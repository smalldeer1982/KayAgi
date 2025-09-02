# [POI 2007] ODW-Weights

## 题目描述

在搬迁到一个新的园区时，Byteotian 实验物理研究所遇到了一个后勤问题——转移其庞大的精密砝码收藏变得不那么简单。

研究所有若干个强度有限的容器可供使用。需要尽可能多地将砝码放入容器中，剩下的将被丢弃。除了不超过容器的强度外，放入容器中的砝码数量没有限制。一个容器也可以是空的。

研究所的任意两个砝码有一个特殊的性质：其中一个的质量是另一个质量的整数倍。特别地，它们可能具有相同的质量。

任务编写一个程序：

从标准输入中读取容器的强度和砝码的质量，确定可以放入容器中的最大砝码数量，将结果写入标准输出。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
2 4
13 9
4 12 2 4```

### 输出

```
3```

# 题解

## 作者：VioletIsMyLove (赞：9)

砝码两两互为倍数关系，从小到大排个序，可以发现不同的砝码种类数是 $log(10^9)$ 级别的，只有 $30$ 左右。

根据贪心的思想，砝码从小到大依次装入一定是最优的,把每个容器的容量写成砝码大小的进制表示，比如当有 $3,9,18,54$ 这些种类的砝码时，$133$ 的容量可以写成 $2*54+1*18+0*9+2*3+1$，末尾的 $+1$ 永远用不上，可以舍弃，
那么各位从低到高分别是 $(2,0,1,2)$。

把所有容器都写成这种表示，并把同一位上全部累加。比如说我们还有一个容器 $(0,1,2,0)$，那么两个容器累加的结果就是 $(2,1,3,2)$。

当我们正在放大小为 $3$ 的砝码时，就使用最低位上的容量。比如我们只有 $1$ 个大小为 $3$ 的砝码，那么塞入以后剩余容量为 $(1,1,3,2)$。

接下来要放大小为 $9$ 的砝码，最低位上的那个 $1$ 就永远用不上了。假如我们有 $2$ 个 $9$，而第二位上只有 $1$ 的容量，那么就往高位借一个 $18$ 拆成两个 $9$，变成 $(2,3,2,2)$，然后塞入后剩余 $(2,1,2,2)$。以此类推。其实就是小学减法嘛，不要搞错，依次借位就ok了。

```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,m,a[maxn],b[maxn],num[maxn],c[35],tot,cnt[35];
int read(){
    int ret=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
    return ret*f;
}
int DFS(int id){//首先核对是否够-，不够要依次借位 
    if (id>tot)return 0; 
    if (cnt[id])return cnt[id]--,1;
    if (DFS(id+1)){
      cnt[id]+=c[id+1]/c[id],cnt[id]--;
      return 1;
    }
    return 0; 
}
int main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++) a[i]=read();
    for (int i=1;i<=m;i++) b[i]=read(); 
    sort(b+1,b+m+1); 
    for (int i=1;i<=m;i++){
      if(b[i]!=b[i-1]) c[++tot]=b[i];
      num[i]=tot;
    }
    for (int i=1;i<=n;i++)
    for (int j=tot;j;j--)
      cnt[j]+=a[i]/c[j],a[i]%=c[j];
    for (int i=1;i<=m;i++){
      if(!DFS(num[i])){printf("%d\n",i-1);return 0;}
      if(i==m)printf("%d\n",m);
    }
    return 0;
} 
```


---

## 作者：LlLlCc (赞：5)

因为题目要求的是最多能装多少个，所以不用管放了哪些，只管放了多少就好了

有一个很显然的结论，如果当前容器放的下一个质量为$a[i]$的砝码，那么肯定也能放的下质量小于$a[i]$的任意砝码

因此，我们可以对砝码的质量$a[i]$从大到小排序。对于第$i$个砝码，先找当前是否有容量大于$a[i]$的容器，如果有就放下，贪心的想法是挑最大的放，每次都挑最大的，自然而然就会想到用堆来维护；如果都放不下，就在前面找一个已经放下$a[j]$且${j<i}$，我们先将$a[i]$放进$a[j]$所在的容器里，再把$a[j]$取出，因为序列呈降序，所以$a[i]<a[j]$，所以现在容器的质量反而增加了，不会溢出，也就是可行解

相见代码：
```
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int tot,Ans,n,m,a[maxn],b[maxn],id[maxn],hed=1,Son,Now,lnk[maxn],M,x,mx;
struct lc{
	int x,id;
}heap[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void Swap(int x,int y){
	lnk[heap[x].id]=y,lnk[heap[y].id]=x;
	swap(heap[x].x,heap[y].x);
	swap(heap[x].id,heap[y].id);
}
inline void put(int x,int id){
	heap[Now=++tot]=(lc){x,id};lnk[id]=Now;
	while (Now!=1&&heap[Now].x>heap[Now>>1].x) Swap(Now,Now>>1),Now>>=1;
}
inline int get(){
	int Mx=heap[1].x;
	Now=1,Son=2;lnk[heap[tot].id]=1;heap[1].id=heap[tot].id,heap[1].x=heap[tot].x;tot--;
	while (Son<=tot){
		if (Son!=tot&&heap[Son+1].x>heap[Son].x) Son++;
		if (heap[Son].x>heap[Now].x) Swap(Now,Son),Now=Son,Son=Now<<1;
		else break;
	}
	return Mx;
}
inline void change(int x){while (x!=1&&heap[x].x>heap[x>>1].x) Swap(x,x>>1),x>>=1;}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read(),put(a[i],i),mx=max(mx,a[i]);
	for (int i=1;i<=m;i++){
    	x=read();
	    if (x>mx) continue;
	    b[++M]=x;
    }
    m=M;
	sort(b+1,b+m+1);reverse(b+1,b+m+1);
	for (int i=1;i<=m;i++){
		if (heap[1].x>=b[i]) Ans++,id[i]=heap[1].id,put(get()-b[i],id[i]);
		else{
			id[i]=id[hed];heap[lnk[id[i]]].x+=b[hed]-b[i];change(lnk[id[i]]);
		    hed++;
		}
	}
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：TheLostWeak (赞：4)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/BZOJ1110.html)

**大致题意：** 有$n$个背包和$m$个砝码，每个背包有一定的重量限制，而砝码两两之间重量都成倍数关系。求最多能把几个砝码装入背包。

### 进制分解

考虑题目中“砝码两两之间重量都成倍数关系”这句话肯定有猫腻，必然要以它为入手点。

将砝码按重量排序并去重后，易知每一个砝码重量至少是前一个砝码的两倍，因此砝码重量的种数总共也只有$log_2(10^9)≈30$种，是非常少的。

设排序去重后第$i$种砝码重量为$a_i$，个数为$b_i$。

我们定义一个特殊的进制，其中第$i$位的位权是$a_i$。

然后我们把背包的容量都按照这种特殊的进制进行进制分解，然后分每一位加在一起。注意，加的过程中不能进位，因为每个背包是独立的。

最后，我们贪心地从小到大枚举每一种砝码。

对于第$i$种砝码，我们操作$b_i$次，每次将第$i$位减$1$。若减成了负数，则去向更高位借位。若无法再借，就说明无法再加砝码。

注意，第$i+1$位的$1$退到第$i$位，会变成$\frac{a_{i+1}}{a_i}$。

具体实现详见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 100000
using namespace std;
int n,m,k,s[N+5],a[N+5],b[N+5],p[N+5];
I bool Dec(CI x)//将第x位减1
{
	RI i;for(i=x;i<=k&&!p[i];++i);if(i>k) return 0;//如果借不到，返回0
	for(--p[i--];i>=x;--i) p[i]+=a[i+1]/a[i]-1;return 1;//借位，返回1
}
int main()
{
	RI i,j,t=0;for(scanf("%d%d",&n,&m),i=1;i<=n;++i) scanf("%d",s+i);
	for(i=1;i<=m;++i) scanf("%d",a+i);sort(a+1,a+m+1);//排序
	for(i=1;i<=m;++i) a[i]^a[i-1]?(a[++k]=a[i],b[k]=1):(++b[k]);//去重，同时统计每种砝码的个数
	for(i=1;i<=n;++i) for(j=k;j;--j) p[j]+=s[i]/a[j],s[i]%=a[j];//进制分解
	for(i=1;i<=k;++i) for(j=1;j<=b[i];++j) if(Dec(i)) ++t;else goto End;//枚举砝码尝试放入
	End:return printf("%d",t),0;//输出答案
}
```



---

## 作者：离散小波变换° (赞：3)

适合老年人锻炼记忆力的萌萌贪心题好啊。

## 题解

注意到题目中一条重要性质：对于任意 $1\le i,j\le m$，必有 $m_i\mid m_j$ 或者 $m_j\mid m_i$。那么假如我们把 $m$ 数组从小到大排序去重放到数组 $m'$ 里，那一定有 $m'_1\mid m'_2\mid m'_3\mid \cdots \mid m'_k$。换一个表现形式，$m'_i=p_1p_2\cdots p_{i-1}\times m'_1$，其中 $1<p_i$，所以最多只会有 $\log v$ 种不同的 $m$。将其用桶存储下来，记第 $i$ 种重量为 $w_i$，数量有 $h_i$ 个。

因为题目只要求求出最多能放多少个砝码，所以可以用一种「反悔」的思想：大砝码总是可以被替换成小砝码而使结果不劣。同时注意到，如果先往容器里放小砝码，有可能出现在不同容器里放了小砝码导致大砝码放不进去的问题。因为我们反悔的思路是把大砝码替换成小砝码，所以最开始先优先放大砝码，即从大到小枚举砝码将其尽可能多地放到容器里。

为什么这样做，不会出现因为大砝码放的容器不同而导致能放进去的小砝码的数量变少呢？这里仍然是使用题目所给的倍数条件。对于两种不同的放大砝码方案，新产生的空挡可以完全被小砝码放进去而相当于一个大砝码。

在这样填充完毕后，剩下来的空隙一定不足以容纳剩下来的最小的砝码。那些边角料已经失去了用途。

接着是考虑反悔。从大到小枚举砝码 $i$，去看看有没有大砝码 $j$ 可以被替换掉。替换的过程仍然是贪心的：拿掉尽可能少的大砝码，使得小砝码都可以放进去，所以被替换的法码 $j$ 的重量仍然是从大到小枚举。拿掉大砝码填充小砝码后可能会产生新的边角料，而这些边角料是可以被使用的（因为这些边角料一定是更小的法码的倍数）。需要拿一个变量存储，填充砝码 $i$ 时优先从边角料开始填充。

上述过程具体实现可以参考代码。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e5 + 3;
const int MAXM=  30 + 3;
int H[MAXM], G[MAXM], W[MAXM];
map<int, int> M;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int A[MAXN], n, m, t, ans; i64 s;
int main(){
    n = qread(), m = qread();
    up(1, n, i) A[i] = qread();
    up(1, m, i) M[qread()] ++ ;
    for(auto &p : M){
        W[++ t] = p.first, H[t] = p.second;
    }
    dn(t, 1, i){
        up(1, n, j){
            if(A[j] >= W[i]){
                int a = min(H[i], A[j] / W[i]);
                H[i] -= a, G[i] += a;
                A[j] -= a * W[i];
                ans += a;
                if(H[i] == 0) break;
            }
        }
    }
    dn(t, 1, i){
        int a = min(1ll * H[i], s / W[i]);
        H[i] -= a, G[i] += a, s -= a * W[i];
        dn(t, i + 1, j) if(G[j]){
            int k = W[j] / W[i];
            int u = min(G[j], H[i] / k + !!(H[i] % k));
            int v = min(1ll * H[i], 1ll * u * k);
            H[i] -= v, G[i] += v;
            H[j] += u, G[j] -= u;
            s = s + 1ll * u * W[j] - 1ll * v * W[i];
            ans = ans + v - u;
            if(H[i] == 0) break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：_Passerby_ (赞：2)

# P3462 题解

## Problem

[题目链接](https://www.luogu.com.cn/problem/P3462)

大意：有 $m$ 个砝码，放到 $n$ 个容器中，每个砝码有重量 $w_i$，每个容器有 $v_i$ 的容量，求最多能放下的砝码数量。

同时，对于任意两个砝码，它们的重量成倍数关系。

## Solution

这道题最关键的线索是：**对于任意两个砝码，它们的重量成倍数关系。** 这个条件意味着，尽管砝码的数量可能非常多，但它们的重量种类实际上是非常有限的。具体来说，由于每个砝码的重量都是其他砝码重量的整数倍（或相等），因此最多只有 $\log_2(10^9) \approx 30$ 种不同的重量级别。这是因为在每个砝码重量都为 $2^k$（$k$ 为非负整数）的极端情况下，砝码的种类数才会达到最大。

那么这道题从哪里入手呢？一般，我们都从题目中较小的数据范围入手。只有最多 $30$ 种砝码，再结合算法标签中的提示，考虑使用进制解决这道题。

我们可以将问题转化为一个“进制拆分”的问题。具体来说，我们可以将每个容器的容量看作是一个由不同重量砝码组成的“数”，而这个“数”的每一位都对应着一种重量的砝码数量。

例如，在样例中，有一个容器的容量是 $13$，而砝码的重量有 $2,4,12$ 这几种。我们可以尝试将 $13$ 拆分成这几种重量的砝码组合。由于 $13=12+1$，但这里的 $1$ 无法用给定的砝码表示（因为没有重量为 $1$ 的砝码，或者即使有也无法单独使用，因为它不满足倍数关系），所以我们可以将其舍去，只考虑 $12$。当然，这个例子有些简化，实际中我们需要考虑所有可能的组合。

需要注意的一点是，拆分是从大往小拆，这点等会会说。

可以看到，题目中的容器是相互独立的，但我们进行进制拆分后就不需要单独考虑了。这是因为我们已经将容器的容量拆分为进制了，所以我们每次放砝码只需要在进制的每一位上加减即可，也就不需要单独考虑了。做法是直接将每个容器拆分，然后将拆分后的进制数加起来。

还是样例中，$13$ 拆分为 $0,0,1$，$9$ 拆分为 $0,2,0$，最后的总容量拆分为 $0,2,1$。

好，我们现在已经完成了总容量的进制拆分了。现在，我们需要考虑往容器里面放砝码了。考虑贪心策略，显然，从小往大放砝码一定是最优的。但如果一个位置没有了怎么办？借位！向它的高一位借一个 $1$。假设高位进制基数为 $a$，需要借位的基数为 $b$，那我们就向高位借走一个 $a$ 容量，在低位就会多 $a / b$ 个 $b$ 容量。具体来说，它表现在进制数第 $k + 1$ 位减 $1$，在进制数第 $k$ 位加 $a/b$。如过 $k + 1$ 位借不了怎么办？借 $k + 2$ 位。$k + 2$ 不行就 $k + 3$，一直到最高位，如果最高位都借不了那也就说明我们再也放不了砝码了。

好了，这就做完了，借位部分写一个 DFS 就行，具体实现参考代码。

代码：[Link](https://www.luogu.com.cn/paste/ih1a9r8h)

---

## 作者：vеctorwyx (赞：2)

## 好像大多数题解都是用的进制，提供一种不太一样的做法

### 题目大意：

$n$ 个背包， $m$ 种物品， 其中任意两个物品的重量都是整数倍关系。

### 解法：

因为重量有倍数关系的限制， 只能是形如 $a, a^2, a^3...$ 这样的， 也就是最多有 $\log_2(10^9) \approx 30$ 种不同的重量。

于是我们可以预处理出每一种重量有多少个物品。

易知对于一个相同的空间，放入重量小的物品一定比放入重量大的物品优。

简单证明：

- 如果两种物品数量一样，则重量小的物品可以剩余更多空间放其他物品；

- 如果两种物品都足够多（能把这个空间填满），则重量小的物品可以放更多个；

- 其他情况可以分组，都会变成前两种情况。

但是重量大的物品灵活性差，即有些地方放不下，会创造出一种劣的情况。

于是我们得到了一种构造方法：

1. 把物品按从大到小枚举，能放就放；

2. 如果有剩余的物品，那么就回去找有没有比当前物品重量大的物品，然后拿重量小的物品替换。

3. 被替换出来的数还有可能接着往后替换，要记得处理。

总时间复杂的 $O(n\log^3n)$ 跑不满， ~~好像能被卡掉？~~

代码写的比较逊，轻喷。。

code：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, ans;
int a[100010], b[100010], fg[100010][33];
int id[100010], ct[100010], cnt;
bool cmp(int x, int y){
	return x > y;
}
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= m; i++)
		scanf("%lld", &b[i]);
	sort(b + 1, b + 1 + m);
	b[0] = -1;
	for(int i = 1; i <= m; i++){
		if(b[i] != b[i - 1])
			id[++cnt] = b[i];
		ct[cnt]++;
	}
	for(int i = cnt; i >= 1; i--){
		for(int j = 1; j <= n; j++){//直接放入
			if(a[j] >= id[i]){
				int dat = a[j] / id[i];
				dat = min(dat, ct[i]);
				a[j] -= dat * id[i];
				fg[j][i] += dat;
				ct[i] -= dat;
				ans += dat;
			}
		}
		if(ct[i] > 0){//多余的物品进行替换
			for(int j = cnt; j > i; j--){
				if(!ct[i])
					break;
				for(int k = 1; k <= n; k++){
					if(!ct[i])
						break;
					if(fg[k][j]){
						int dat = min(id[j] / id[i] * fg[k][j], ct[i]);
						a[k] += (ceil(1.0 * dat * id[i] / id[j] - 1e-10)) * id[j];
						fg[k][j] -= (ceil(1.0 * dat * id[i] / id[j] - 1e-10));
						ans -= ceil(1.0 * dat * id[i] / id[j] - 1e-10);
						ct[j] += ceil(1.0 * dat * id[i] / id[j] - 1e-10);
						a[k] -= dat * id[i];
						fg[k][i] += dat;
						ans += dat;
						ct[i] -= dat;
					}
				}
			}
		}
	}
	for(int ti = 1; ti <= cnt; ti++){//被替换出来的再次进行处理
		for(int i = cnt; i >= 1; i--)
			if(ct[i] > 0){
				for(int j = cnt; j > i; j--){
					if(!ct[i])
						break;
					for(int k = 1; k <= n; k++){
						if(!ct[i])
							break;
						if(fg[k][j]){
							int dat = min(id[j] / id[i] * fg[k][j], ct[i]);
							a[k] += (ceil(1.0 * dat * id[i] / id[j] - 1e-10)) * id[j];
							fg[k][j] -= (ceil(1.0 * dat * id[i] / id[j] - 1e-10));
							ans -= ceil(1.0 * dat * id[i] / id[j] - 1e-10);
							ct[j] += ceil(1.0 * dat * id[i] / id[j] - 1e-10);
							a[k] -= dat * id[i];
							fg[k][i] += dat;
							ans += dat;
							ct[i] -= dat;
						}
					}
				}
			}
	}
	printf("%lld\n", ans);
	return 0;
}
```

PS : 数据很水，如果你认为我的做法是假的，欢迎 hack。

---

## 作者：大菜鸡fks (赞：2)

这题主要思想就是进制拆分吧。

先把容器进制拆分，并且各容器每位相加（不进位）。

由于log（1e9）=30 所以，复杂度可以接受。

取用的时候遵循能取 则取。不能取就借用高位上的，高位上的物品可以退位。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,m,a[maxn],b[maxn];
inline void init(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for (int i=1;i<=m;i++){
		scanf("%d",&b[i]);
	}
}
int c[maxn],cnt[maxn],tot;
inline bool judge(int x){
	for (int i=x+1;i<=tot;i++){
		if (cnt[i]){
			cnt[x]+=c[i]/c[x];
			cnt[i]--;
			return 1;
		}
	}
	return 0;
} 
inline void solve(){
	sort(b+1,b+1+m);
	for (int i=1;i<=m;i++){
		if (b[i]!=b[i-1]){
			c[++tot]=b[i];
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=tot;j;j--){
			while(c[j]<=a[i]){
				a[i]-=c[j];
				cnt[j]++;
			}
		}
	}
	int now=1;
	for (int i=1;i<=m;i++){
		while (b[i]>c[now]) now++;
		if (cnt[now]) cnt[now]--;
			else if (judge(now)) cnt[now]--;
				else {
					printf("%d\n",i-1);
					return;
				}
		if (i==m) printf("%d\n",m);
	}
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：HHH6666666666 (赞：1)

一个与进制关系不大的做法。首先既然重量只有 $\log(V)$ 种，不妨从小到大考虑每种重量的放置。

大小相邻的重量必成倍数关系，这给了我们一些自然的想法：

不妨令当前重量为 1，下一个重量为 $k$。我们应优先将这些重为 1 的砝码放入哪些位置？显然是 $k \nmid w_i$ 的位置。因为其余所有重量必然为 $k$ 的倍数，每个位置中余下的容量会被舍弃。

在使所有位置的容量均为 $k$ 的倍数后，这些 1 又改放哪呢？假如此时剩余 $x$ 个 1，这就等价于放置 $\frac{x}{k}$ 个重量于价值均为 $k$ 的物品，保留到下一层做即可。可能无法整除，但由于所有位置上的剩余容量都是 $k$ 的倍数，可以将体积同样视为 $k$，多的那部分反正没用。

实现时：

1. 既然赋予了物品不同价值就应该在同层贪心地优先选取价值更大的物品。合并时同理。

2. 特判无后继（即当前为最大价值）的情况。

理论复杂度为 $O((n+m)\log(V))$，实现时可能会多一两只 $\log$。

---

## 作者：LeBao2023 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P3462)

有许多个砝码，这些砝码是倍数关系，而且每个砝码都不是太重，所有 $m_i \le 10^9$，所以不同的砝码个数顶多就是 $\log(10^9) \approx 32$ 种。

我们可以考虑使用类似二进制拆分的方法，把每个容器拆开，看他可以装下多少的那样重的砝码。

用样例举个例子，$13=12 \times 1+1,9=4 \times 2+1$，则容器可以装下 $1$ 个 $12$ 和 $2$ 个 $4$ 那么重的砝码，答案是 $3$。

你以为这样就对了吗？我们看一下这个例子

`4 2 4 5 2 4 2 4`

在这个例子中，答案显然是 $3$，方案是容器一装 $2$ 个重 $2$ 的砝码，容器二装 $1$ 个重 $4$ 的砝码，但是以上面那种方法只能算出 $4=4 \times 1+0,5=4 \times 1+1$，装下两个重为 $4$ 的砝码。

所以，我们可以考虑退位，让一个 $4$ 的容量变成两个 $2$ 的容量。

那就要问了，如果退位下来会有剩余，使答案更少怎么办？其实，只要退下来一位，就至少可以再放一个砝码，最差的情况也不会变少，一个大砝码和一个小砝码都是一个，放小的还可能多放。

具体实现看代码。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int n,m,ans=0;
int w[maxn];
int gs[55];
int num[55],g[55];
int cnt=0;
void dfs(int id,int y)
{
	if(id>cnt)
	{
		return ;
	}
	if((num[id]/num[y])*gs[id]<g[y])
	{
		g[y]-=(num[id]/num[y])*gs[id];
		ans+=(num[id]/num[y])*gs[id];
		gs[id]=0;
		dfs(id+1,y);
		return ;
	}
	else
	{
		gs[id]-=(g[y]-1)/(num[id]/num[y])+1;
		ans+=g[y];g[y]=0;
		return ;
	}
}
int a[maxn];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++)
	{
		if(a[i]!=a[i-1])
		{
			g[++cnt]=1;
			num[cnt]=a[i];
		}else
		g[cnt]++;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=cnt;j>=1;j--)
		{
			gs[j]+=w[i]/num[j];
			w[i]=w[i]%num[j];
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		dfs(i,i);
		if(g[i]!=0)
		{
			break;
		}
	}
	cout<<ans;
}
```

---

## 作者：zong15632539rongjuan (赞：0)

##### 题意翻译
这是一道 $2007$ 年 POI 的题目，翻译内容是洛谷这道题的题意翻译。  
在 byteotian 公司搬家的时候，他们发现他们的 $m$ 个大量的精密砝码的搬运是一件恼人的工作。公司有 $n$ 个固定容量的容器可以装这些砝码。他们想装尽量多的砝码以便搬运，并且丢弃剩下的砝码。

每个容器可以装的砝码数量没有限制，但是他们能够装的总重量不能超过每个容器的限制。第 $i$ 个容器允许装下的砝码总重为 $w_i$。一个容器也可以不装任何东西。

此外，这些砝码有一个特征。对于任意两个砝码 $i$，$j$，它们的重量成倍数关系，即 $m_i\mid{m_j}$ 或者 $m_j\mid{m_i}$ 或者两者都成立（即重量相等）。
##### 数据结构
###### 数组
所有的混合进制数都可以用高精度数组存储，最多需要 $\log{10^9}=30$ 个下标的空间。
##### 算法
- 搜索
- 贪心
- 进制
###### 搜索
用搜索进行减法的退位，如果这一位够减，就减这一位。如果这一位不够减，就不断往前一位找，直到找到可以退位到这一位、使这一位够减的位。
###### 贪心
把砝码从小到大排序，先装重量小的砝码，因为装的砝码的重量越小，装的砝码数量越多。
###### 进制
可以把 $w_i$ 的第 $j$ 位改成从小到大排序并去重后的 $m_j$ 进制。我们拿输入样例举例。$w_1=13=1\times12+0\times4+0\times2+1$。因为 $1$ 一定装不下任何砝码，所以我们把 $1$ 忽略掉。我们可以得到一个混合进制的数：$100$。$w_2=9=0\times12+2\times4+0\times2+1$。因为 $1$ 一定装不下任何砝码，所以我们把 $1$ 忽略掉。我们可以得到一个混合进制的数：$010$。这两个数加到一起就是容器允许装下砝码的总重的混合进制：$110$。
##### 过程分析
1. 把 $m$ 数组**排序**。
2. 找到所有的 $m_j$ **进制**。
3. 把 $w_i$ **转成** $m_j$ 进制。
4. 找到每个进制都在混合进制数的**第几位**。
5. 找到**最多能把几个砝码放进容器**。
##### 代码
```
#include <cstdio>
#include <algorithm>
using namespace std;
const int max_n = 110000, max_log_1e9 = 40;
inline int n, m, w[max_n], mm[max_n], ans;
inline int jz[max_log_1e9], len, temp;
inline int mjz[max_log_1e9], nu[max_n], d;
int f(int y) {
    if (y > len)
        return 0;
    if (mjz[y]) {
        mjz[y]--;
        return 1;
    }
    if (f(y + 1)) {
        mjz[y] += jz[y + 1] / jz[y];
        mjz[y]--;
        return 1;
    } else
        return 0;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) 
        scanf("%d", &w[i]);
    for (int j = 1; j <= m; ++j) 
        scanf("%d", &mm[j]);
    sort(mm + 1, mm + m + 1);
    for (int i = 1; i <= m; ++i)
        if (mm[i] != mm[i - 1])
            jz[++len] = mm[i];
    for (int i = 1; i <= n; ++i) {
        temp = w[i];
        for (int j = len; j >= 1; j--) {
            mjz[j] += temp / jz[j];
            temp %= jz[j];
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (mm[i] != mm[i - 1])
            ++d;
        nu[i] = d;
    }
    for (int i = 1; i <= m; ++i)
        if (f(nu[i]))
            ans = i;
        else
            break;
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

由于给定的 $m$ 个精密砝码两两成倍数关系，所以最多有 $30$ 个不同重量的砝码。

将给出的 $n$ 个箱子按照砝码进行一次进制拆分，然后对于每一个砝码的重量，按照从小到大的顺序贪心地计算即可。注意如果一个砝码对应的箱子数量不够，那么可以从更高一级的箱子中找。

如果轮到一个砝码的时候剩下所有的箱子都放不下所有的了，那么放尽量多的，很显然剩下的更大的砝码都放不下去了，所以直接计算答案即可。

由于不同的砝码的数量很少，所以直接多层循环暴力枚举即可。

这个题真的没有紫吧。

---

## 作者：_Revenge_ (赞：0)

本文与 [此博客](https://www.cnblogs.com/R-V-G/) 同步。

#### Aim 1：题目大意

$n$ 个容器，$m$ 个砝码。     
求最大能装下多少砝码。    
较为特别的砝码的质量两两成倍数关系。     

看起来是什么背包，但是。     
所以我们要抓住**砝码的质量两两成倍数关系**。    
这里显然暗藏玄机，其实很容易可以想到这和进制有关系，毕竟进制的每一位的权值都是倍数关系，如果没有这个砝码只是这一位为 $0$ 罢了。          


#### Aim 2：砝码进制

此时我们有两个容器质量 $13\ 9$。     
这里有四个砝码 $2\ 4\ 4\ 12$。     

我们对容器进行砝码进制转化。

$13=(0,0,1)+1$。

每一位从小到大表示砝码质量，而最后剩下的数将对答案没有贡献。

同理 $9=(0,2,0)+1$ 。     

将两个砝码进制数相加，可得：

$(0,2,1)$。

这样做的原因：我们知道它们成倍数关系，那么如果高位可以放下那么低位可以类似借位的形式向高位要。      
剩下的部分一定小于任意砝码，不能被利用。    
如果不懂可以多想想，不然您无法理解。        

#### Aim 3：贪心借位

既然这样我们已近处理好了，我们发现无论做大的还是小的，其贡献均一致，那么显然！

先做质量小的。

此时我们做 $2$ 但是没有，就向下一位借位。 

$(2,1,1)$。

用掉一个 $2$，但是剩一个则对后面没有贡献。     

$(0,1,1)$ 贡献 $1$。

此时遇到两个 $4$，用掉一个并向后借位，并可装下两个，但是剩余则对后面没有贡献。

$(0,0,0)$ 贡献 $3$。

此时我们得到了代码，在代码实现上注意借位的问题，即可解决，感谢观看！

代码经过格式化，用餐愉快。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N = 1e5 + 50;
const int M = 1e5 + 50;
const int Mod = 1e9 + 7;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int n, m, cnt;

int a[N], b[N], c[N], d[N], num[N];

void dfs(int step, int now)
{
    if (step == cnt + 1)
        return;
    if (c[step] && step == now)
        return;
    if (c[step])
    {
        c[step]--;
        c[step - 1] += b[step] / b[step - 1];
        return;
    }
    else
    {
        dfs(step + 1, now);
        if (c[step] && step != now)
            c[step]--, c[step - 1] += b[step] / b[step - 1];
    }
}

signed main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= m; ++i)
        b[i] = read(), d[i] = b[i];
    sort(d + 1, d + m + 1);
    cnt = 0;
    for (int i = 1; i <= m; ++i)
        if (d[i] != d[i - 1])
            b[++cnt] = d[i], num[cnt]++;
        else
            num[cnt]++;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = cnt; j >= 1; --j)
        {
            c[j] += a[i] / b[j];
            a[i] %= b[j];
        }
    }
    for (int i = 1, j = 1; i <= cnt; ++i)
    {
        while (num[i]--)
        {
            dfs(i, i);
            if (c[i])
                c[i]--;
            else
            {
                printf("%d\n", j - 1);
                return 0;
            }
            ++j;
        }
    }
    printf("%d\n", m);
    return 0;
}
```

---

