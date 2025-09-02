# [USACO20OPEN] Cereal S

## 题目描述

Farmer John 的奶牛们的早餐最爱当然是麦片了！事实上，奶牛们的胃口是如此之大，每头奶牛一顿饭可以吃掉整整一箱麦片。

最近农场收到了一份快递，内有 $M$ 种不同种类的麦片（$1\le M\le 10^5$）。不幸的是，每种麦片只有一箱！$N$ 头奶牛（$1\le N\le 10^5$）中的每头都有她最爱的麦片和第二喜爱的麦片。给定一些可选的麦片，奶牛会执行如下的过程：

- 如果她最爱的麦片还在，取走并离开。
- 否则，如果她第二喜爱的麦片还在，取走并离开。
- 否则，她会失望地哞叫一声然后不带走一片麦片地离开。

奶牛们排队领取麦片。对于每一个 $0\le i\le N-1$，求如果 Farmer John 从队伍中移除前 $i$ 头奶牛，有多少奶牛会取走一箱麦片。

## 说明/提示

### 样例解释
如果至少两头奶牛留下，那么恰有两头奶牛取走了一箱麦片。

### 子任务
- 测试点 $2$-$3$ 满足 $N,M\le 10^3$。
- 测试点 $4$-$10$ 没有额外限制。

## 样例 #1

### 输入

```
4 2
1 2
1 2
1 2
1 2```

### 输出

```
2
2
2
1```

# 题解

## 作者：PersistentLife (赞：32)

[博客阅读体验更佳](https://www.luogu.com.cn/blog/302837/solution-p6282)

### Level $1$：

我们很容易想到，从 $0$ 到 $N-1$ 枚举，然后模拟奶牛选择麦片的过程。

其中 $h_i$ 表示第 $i$ 种麦片被选择的情况，$c_i$ 表示第 $i$ 头奶牛喜欢的麦片。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=123456;
struct cow
{
	int f,s;
}c[N];
bool h[N];
int n,m;
void init()
{
	for(int i=1;i<=n;i++) h[i]=1;
}
void solve(int x)
{
	int ans=0;
	init();
	for(int i=x+1;i<=n;i++)
	{
		if(h[c[i].f])
		{
			ans++;
			h[c[i].f]=0;
		}
		else if(h[c[i].s])
		{
			ans++;
			h[c[i].s]=0;
		}
	}
	cout<<ans<<endl;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i].f>>c[i].s;
	for(int i=0;i<n;i++) solve(i);
	return 0;
}
```

这份代码只有 $30$ 分，其余 TLE 了。

我们从 $0$ 到 $N-1$ 都进行了枚举，而每次算答案的时候要遍历每一头牛，所以时间复杂度为 $\Theta(N^2)$。

这里 $N \le 10^5$，所以我们的复杂度是不行的。

因为我们要算出 $N$ 个答案，所以复杂度至少为 $\Theta(N)$，故我们只能优化 $solve$ 函数。

### Level $2$：

我们想想，当减少一头牛时，会发生什么情况？

- 如果它选择了麦片，那么它的麦片可能被其他奶牛选择；

- 如果没有选择麦片，那么答案不会改变。

但是，这样还是要找一下有哪头奶牛需要这个麦片，所以优化不了多少。

怎么办呢？~~大家跟我一起念：我们遇到什么困难，也不要怕，微笑着面对它……~~

如果我们增加奶牛，即倒着求每个答案，最后倒着输出就行了。

如果增加一头奶牛，又会出现什么情况呢？

- 如果它最喜欢的麦片没有被选择，那么它就会选它，且不影响其他奶牛；

- 如果它最喜欢的麦片被选择，因为它的优先级比其他牛都高，所以会把其他牛的麦片“抢”过来，其他牛只能“退而求其次”。

这样代码就很好写啦，递归求解即可，因为所有奶牛最多选两次，所以 $solve$ 函数的复杂度是 $\Theta(1)$ 的，整个代码的时间复杂度为 $\Theta(N)$。

实现方法见代码注释：

$c_i$ 表示第 $i$ 头奶牛的喜好，$h_i$ 表示拿走第 $i$ 种麦片的牛的编号，$res_i$ 表示移走 $i-1$ 头牛的答案，$cur$ 是计算答案的计数器。

因为领麦片的牛越多，领到麦片的牛就越多，所以越往后面，$cur$ 就越大，故每次计算的时候 $cur$ 不需要清零。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=123456;
struct cow
{
	int f,s;
}c[N];
int h[N],res[N],n,m,cur;
void solve(int x,int y)//x表示目前是哪一头牛选麦片，y表示目前要选择的麦片 
{
	if(h[y]==0)//最喜欢的未拿走 
	{
		h[y]=x;//拿走它
		cur++;//计数器加一 
	}
	else if(h[y]>x)//虽然麦片被拿走，但是当前的牛有排在前面，依然可以拿走
	{
		int z=h[y];//要重选的奶牛编号 
		h[y]=x;//拿走，这里不需要加一，因为之前拿走麦片的牛和现在拿走麦片的牛都是牛 
		if(y==c[z].f) solve(z,c[z].s);//如果"抢"过来了，那么另一头牛就要重选 
	} 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i].f>>c[i].s;
	for(int i=n-1;i>=0;i--) solve(i+1,c[i+1].f),res[i+1]=cur;
	for(int i=1;i<=n;i++) cout<<res[i]<<endl;
	return 0;
}
```


---

## 作者：kradcigam (赞：11)

[题面](https://www.luogu.com.cn/problem/P6282)

这道题我是用队列做的。我们想一想少掉 $1$ 头奶牛，整个奶牛队列会发生什么变化

首先，最前面的那头奶牛走了，就空出来了他最喜欢吃的那包麦片了。

这包麦片可能会造成如下反应：
	
   - 一头奶牛原来吃的是它第 $2$ 喜欢的麦片，现在它吃自己第 $1$ 喜欢的了，使得又空出了一包麦片。
   - 一头奶牛原来没有东西吃，现在它吃到了它 第1/第2 喜欢的麦片。

我们可以写一个队列来计算这个东西，由于队列是先进先出，正好符合排队的顺序。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int MAXN=1e5+10;
int n,m,f[MAXN],s[MAXN],k[MAXN],sum[MAXN],x[MAXN],ans;
queue<int>v[MAXN];
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)read(f[i]),read(s[i]);
	for(int i=1;i<=n;i++){//x的值为1，表示吃它第1喜欢的麦片；x的值为2，表示它第2喜欢的麦片；x的值为3，表示他没吃到麦片
		if(!k[f[i]])k[f[i]]=1,x[i]=1,ans++;
		else if(!k[s[i]])v[f[i]].push(i),k[s[i]]=1,x[i]=2,ans++;
			else v[f[i]].push(i),v[s[i]].push(i),x[i]=3;
	}//暴力求出所有奶牛的情况
	cout<<ans<<endl;
	for(int i=1;i<n;i++){
		int xx=f[i];//离开的那头奶牛最喜欢吃的麦片
		ans--;
		while(v[xx].size()){
			int q=v[xx].front();
			v[xx].pop();
			if(x[q]==2){
				xx=s[q];
				x[q]=1;
			}
			if(x[q]==3){
				ans++;
				if(f[q]==xx)x[q]=1;
				else x[q]=2;
				break;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

复杂度分析：这个代码的复杂度其实是 $O(n)$ 的，因为我们最多队列里的每个元素访问 $1$ 次，然后队列里元素个数是 $2n$ 的。

---

## 作者：super蒟蒻 (赞：10)

提供一种顺着推的思路。

首先考虑求每头奶牛在哪个时间点可以拿到麦片，然后用差分处理，做个前缀和就能得到答案了。

那么先需要维护一个 $p$ 数组，$p(i,x)$ 表示**在前 $i$ 头牛中**，第 $x$ 种麦片最后被拿是在哪头牛上（也可以理解为：对于前 $i$ 头牛而言，在第 $p_x$ 头牛**之后**第 $x$ 种麦片就没有牛会拿了 ）。

注意这个 $p$ 数组是用来**辅助**后面求答案的。

而且一开始，在第一头牛之前，$p$ 数组全是 0 ，肯定是对的，那么只需要确保此后每次能更新对 $p$ 数组就行。

假设现在考虑到第 $i$ 头奶牛，显然，这头奶牛能拿到麦片的时间点就是 $\min(p(i - 1,f_i), p(i - 1, s_i)) + 1$ 。(就是看这两种麦片哪种最先能拿)

那么再考虑更新 $p$ 数组，首先肯定的是 $p$ 数组**只可能**在两个位置改变，并且实现的时候也不需要开两维，直接覆盖就行。

1. $p(i,f_i) = i$ 。

   因为第 $i$ 头首要就是拿麦片 $f_i$ 。
   
   如果没轮到第 $i$ 头牛，那么前面一定有牛拿了；否则就是第 $i$ 头牛拿了。
   
   **但不需要管是谁**，总之不删除到第 $i$ 头，麦片 $f_i$ 就是会被拿，**后面的牛**就是不能要。
   
   因此， $p(i,f_i) = i$ 。（所以说 $p$ 数组是考虑对后面的牛的影响的）

2. $p(i,s_i) = max(p(i - 1, s_i),p(i - 1,f_i))$ 。

	可能会有点难理解，但是可以仿照上面的思路。

   首先第 $i$ 头牛选择第二重要的麦片的**前提**是，麦片 $f_i$ 被拿了。
   
   那么就是在 $p(i-1,f_i)$ 之前，奶牛 $i$ 只会选择麦片 $s_i$ 。
   
   同上，如果没轮到第 $i$ 头牛，那么麦片 $s_i$ 在前面一定有牛拿了；否则就是第 $i$ 头牛拿了。
   
   **但不需要管是谁**，总之**至少**， **不**删除到第 $p(i-1,f_i)$ 头牛，麦片 $s_i$ 就是会被拿，后面的牛就是不能要。
   
   但是这里的值与上面不同，不是 $i$ ，即不是最大的，它不一定能更新 $p$ 数组，所以跟原先取个 $\max$ 就好。
   
那么这个题就做完了，代码实现起来也很简单。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000005;
int n, m;
int p[maxn], s[maxn];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        ++s[min(p[a], p[b]) + 1];
        --s[i + 1];
        p[b] = max(p[b], p[a]);
        p[a] = i;
    }
    for (int i = 1; i <= n; i++) printf("%d\n", s[i] += s[i - 1]);
    return 0;
}
```

---

## 作者：Na2PtCl6 (赞：4)

## 分析题目
题目要我们求区间 $[a_1,a_n]$，$[a_2,a_n]$，$[a_3,a_n]$ ，$...$ ，$[a_{n-2},a_n]$ $,[a_{n-1},a_n]$ 中的奶牛分别有多少头能拿到多少麦片，而每种麦片只有一个，那就意味着先到先得，即 **位置较靠前的奶牛取走的麦片不能被位置较靠后的奶牛取走** 。

所以我们考虑从后往前遍历每一头牛，如果这头牛 **喜欢的麦片没有被取走就取** 并结果加一，反之就看是否 **有牛拿了这头牛喜欢麦片但是位置较靠后** ，如果是，就把麦片“抢”过来，并且用同样的方法更新被“抢劫”的牛，如果不是就没有麦片可以拿了。不管是奶牛没有拿到麦片还是“抢”了其他奶牛的麦片 **结果都是不变的** ，因为总有一头牛没有麦片。然后把总数存一下就行了。

## 代码实现
```cpp
#include<bits/stdc++.h>
#define R return 
using namespace std;
const int maxn=100004;
int n,m,cnt,vis[maxn],res[maxn],f[maxn],s[maxn];

void solve(int cow){
	int fir=f[cow],sec=s[cow];
	if(!vis[fir]){  //如果这头牛最喜欢的麦片还在 
		++cnt;  //又有一头牛得到了麦片 
		vis[fir]=cow;  //这个麦片归当前这头奶牛所有 
		R;  //及时结束,这样就不会影响后面的判断,后面同理 
	}
	if(vis[fir]>cow){   //如果之前拥有这箱麦片的奶牛较靠后
		int t=vis[fir];  //记录之前有这箱麦片的奶牛,避免受更新的影响 
		vis[fir]=cow;  //把麦片"抢"过来 
		solve(t);R;  //给被"抢劫"的奶牛重新选麦片 
	}
	//以下同理 
	if(!vis[sec]){
		++cnt;
		vis[sec]=cow;R;
	}
	if(vis[sec]>cow){
		int t=vis[sec];
		vis[sec]=cow;
		solve(t);
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&f[i],&s[i]);
	for(int i=n;i>0;i--){
		solve(i);
		res[i]=cnt;  //因为是倒着处理的,所以不能马上输出 
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",res[i]);
	return 0;
}
```

---

## 作者：Haphyxlos (赞：3)

# P6282 [USACO20OPEN] Cereal S

[题目传送门](https://www.luogu.com.cn/problem/P6282)

## 30分做法

首先，我们不难想到一个$O(n^{2})$解法，只要按照题意暴力模拟即可，可拿到30pts。

### 核心代码
```cpp
int n,m,a[maxn][2];
bool vis[maxn];
for(int i=1;i<=n;++i){
  int cnt=0;
  memset(vis,true,sizeof(vis));
  for(int j=i;j<=n;++j){
      if(vis[a[j][0]])vis[a[j][0]]=false,cnt++;
      else if(vis[a[j][1]])vis[a[j][1]]=false,cnt++;
  }
}
```
## 100分做法

### 样例推导

接着，我们不妨倒着来推一下样例：

当$i=4$时，麦片1被第四头牛拿走了，$ans=1$

当$i=3$时，麦片1被第三头牛拿走了，麦片2被第四头牛拿走了，$ans=2$

当$i=2$时，麦片1被第二头牛拿走了，麦片2被第三头牛拿走了，$ans=2$

当$i=1$时，麦片1被第一头牛拿走了，麦片2被第二头牛拿走了，$ans=2$

### 形象的理解

其实上面的过程，我们完全可以看做是第四头牛本来能拿走自己最喜欢的麦片1，结果第三头牛过来，把第四头牛挤走了，第四头牛就拿走了自己第二喜欢的麦片2。

可是，第二头牛过来了，它把第三头牛挤走了，拿走了麦片1，第三头牛因为被挤走了，就又把第四头牛挤走了，拿走了麦片2，第四头牛难过地离开了。

同理，第一头牛过来了，它把第二头牛挤走了，拿走了麦片1，第二头牛因为被挤走了，就又把第三头牛挤走了，拿走了麦片2，第三头牛难过地离开了。

我们再来简单地证明一下时间复杂度为什么正确。

本题的复杂度应该是$o(n)$的，因为每头牛只能选2个自己喜欢的，所以最多只能操作$2n$次，复杂度正确。

那么代码其实就很好写了。

### 核心代码
```cpp
inline void work(int x,int y,int t=0){
	if(!vis[y])vis[y]=x,cnt++;//当前麦片还没被拿走 
	else if(vis[y]>x){//当前麦片被拿走了 
		t=vis[y],vis[y]=x;
		if(y==a[t][0])work(t,a[t][1]);
	}
}

for(int i=n;i;--i){
	work(i,a[i][0]),ans[i]=cnt;
}
for(int i=1;i<=n;++i){
	printf("%d\n",ans[i]); 
}
```

其中值得注意的是，cnt是可以不用清零的，因为cnt始终都是一个累加的过程。

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：hhhyyyfff (赞：3)

- 题意简述：  
  有 $N$ 头牛，$M$ 箱麦片，每头牛有最喜欢的麦片和其次喜欢的麦片。牛排成一列，一次挑选麦片，若最喜欢的和其次喜欢的麦片都被挑走了，则不会挑走麦片。农夫约翰会移走队伍前 $i$ 头牛 $(0 \le i \le N-1)$，求有几头牛为拿走麦片。

- 算法分析 $O(N)$：从 $N$ 到 $1$ 枚举奶牛，依次让该奶牛拿走最喜欢的麦片，若该麦片原本被拿走，则让原本拿走该麦片的奶牛，退而求其次，以此类推，具体看代码注释。因为每头奶牛最多会选两次，复杂度为 $O(N)$。

- 代码：

``` cpp
#include <cstdio>

using namespace std;

int N, M, cnt, f[100010], s[100010], bel[100010], ans[100010];

void dfs(int x, int y) {
    if (!bel[y]) { //没被拿走
        bel[y] = x; //直接拿走
        ++cnt;
    } else if (bel[y] > x) { //被编号大的牛那走（即当前的牛有优先权）
        int tmp = bel[y];
        bel[y] = x; //拿走
        if (y == f[tmp]) dfs(tmp, s[tmp]); //退而求其次
    }
}

int main() {
    freopen("cereal.in", "r", stdin);
    freopen("cereal.out", "w", stdout);
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) scanf("%d%d", &f[i], &s[i]);
    for (int i = N; i > 0; --i) {
        dfs(i, f[i]); //拿走最喜欢的
        ans[i - 1] = cnt;
    }
    for (int i = 0; i < N; ++i) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：信守天下 (赞：2)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6282)
## 思路
**第一个思路**

直接暴力枚举，时间复杂度 $\Theta(N^2)$，只有$30$分。

原因是每删除一头牛就要从头算一遍。

**第二个思路**

我们可以想到，删除一头牛要重新算，但加入一头牛很简单。

所以我们可以倒序处理每一头奶牛，每次插入一头奶牛在队头。

那么只要有奶牛有冲突，那么当前奶牛的优先级是最高的。

那么就会有两种情况。

* 一头牛最爱的麦片被抢了，但它抢了它第二喜爱的麦片，引起了新的冲突。

* 一头牛第二喜爱的麦片被抢了，她失望地哞叫一声然后不带走一片麦片地离开。

所以我们如果出现第一种要继续解决冲突，直到出现第二种。
## $code$
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
struct E {
  int c[2], p;  // 喜欢的麦片编号、当前选择的下标
} e[kMaxN];
int a[kMaxN], b[kMaxN];  // 答案、选择每种麦片的奶牛
int n, m;
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].c[0] >> e[i].c[1];
  }
  e[0].p = 2;                            // 初始化判断边界
  for (int i = n, s = 0; i >= 1; i--) {  // 倒序加入奶牛
    for (int j = i; e[j].p < 2;) {       // 不断解决冲突
      int x = e[j].c[e[j].p++];          // 当前奶牛要选的麦片
      if (j < b[x]) {                    // 当前奶牛优先级更高
        swap(b[x], j);                   // 切换选择，继续处理换掉的奶牛
      } else if (!b[x]) {                // 当前麦片未被选择
        b[x] = j;
        s++;  // 增加答案
        break;
      }
    }
    a[i] = s;  // 记录答案
  }
  for (int i = 1; i <= n; i++) {
    cout << a[i] << endl;
  }
  return 0;
}
~~~

---

## 作者：jiang_cheng (赞：1)

## 解题思路：
暴力是很容易想到的，就是每次模拟一遍奶牛选麦片就行了。但这样做复杂度太高，所以得换种方法。

想一想，减少一头奶牛会怎么样：首先，如果它选择了麦片，它就会空出它选择的麦片。否则，也不会影响其他奶牛。但这样做有点难模拟，所以我们可以倒着来，考虑从后往前增加奶牛。

如果增加一头奶牛：新奶牛它的优先级是目前最高的，所以它就可以拿自己最喜欢的麦片，就有可能与其他奶牛发生冲突，这时我们循环处理冲突，让其他奶牛选第二喜欢的麦片，如果它第二喜欢的麦片也没了，它就不选，后面的奶牛选择的麦片不会改变，冲突也就没有了。
## 附上代码：
```cpp
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {
  int c[2], p;  // 喜欢的麦片编号、当前选择的下标
} e[kMaxN];
int a[kMaxN], b[kMaxN];  // 答案、选择每种麦片的奶牛
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].c[0] >> e[i].c[1];
  }
  e[0].p = 2;                            // 初始化判断边界
  for (int i = n, s = 0; i >= 1; i--) {  // 倒序加入奶牛
    for (int j = i; e[j].p < 2;) {       // 不断解决冲突
      int x = e[j].c[e[j].p++];          // 当前奶牛要选的麦片
      if (j < b[x]) {                    // 当前奶牛优先级更高
        swap(b[x], j);                   // 切换选择，继续处理换掉的奶牛
      } else if (!b[x]) {                // 当前麦片未被选择
        b[x] = j;
        s++;  // 增加答案
        break;
      }
    }
    a[i] = s;  // 记录答案
  }
  for (int i = 1; i <= n; i++) {
    cout << a[i] << endl;
  }
  return 0;
}
```


---

## 作者：Parat_rooper (赞：1)

***解题思路：***

第一眼看到题面就想到了 $30$ 分的暴力，复杂度为 $\Theta(N^2)$ 。

那应该怎么优化呢？

首先我们可以模拟所有奶牛选麦片的情况，然后按照题意逐个删掉靠前的奶牛并分析情况的变化。

一只奶牛被删除时，可能会空出一种麦片可选，我们可以为所有的麦片按照编号顺序维护一个待选列表，如果当前选它的奶牛被删掉了，那么就轮到下一头奶牛选它。

同理，如果一头奶牛更换了选取的麦片，也会导致一种麦片进入待选，处理方法同上。

最后，维护麦片待选列表比较麻烦，我们可以倒序处理，每次增加一头奶牛，这样就只要维护当前选择和备选就好了。

代码如下：
```cpp
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {
  int c[2], p;  // 喜欢的麦片编号、当前选择的下标
} e[kMaxN];
int a[kMaxN], b[kMaxN];  // 答案、选择每种麦片的奶牛
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].c[0] >> e[i].c[1];
  }
  e[0].p = 2;                            // 初始化判断边界
  for (int i = n, s = 0; i >= 1; i--) {  // 倒序加入奶牛
    for (int j = i; e[j].p < 2;) {       // 不断解决冲突
      int x = e[j].c[e[j].p++];          // 当前奶牛要选的麦片
      if (j < b[x]) {                    // 当前奶牛优先级更高
        swap(b[x], j);                   // 切换选择，继续处理换掉的奶牛
      } else if (!b[x]) {                // 当前麦片未被选择
        b[x] = j;
        s++;  // 增加答案
        break;
      }
    }
    a[i] = s;  // 记录答案
  }
  for (int i = 1; i <= n; i++) {
    cout << a[i] << endl;
  }
  return 0;
}

---

## 作者：Jayun (赞：1)

# 题目大意：

有 $n$ 头牛，每头牛喜欢两款麦片，每款麦片只有一份。编号小的牛先选，每头牛先选它最爱的麦片，若没有则选择第二喜欢的，还没有就不吃了。最后问有多少头牛有麦片。

# 正文：

题目并没有强制在线，虽然可以在线进行操作但是会很麻烦，所以这里考虑从题目中的“移除奶牛”变为“加入奶牛”（即倒着算）。

倒着枚举每头奶牛，如果喜欢的麦片没有被拿走，就直接拿走麦片，否则如果拿走那个麦片的牛的编号要比这头牛的编号要大的话就抢走那个麦片，让原先麦片主去那它第二喜欢的麦片。

# 代码：

```cpp
void dfs(int n, int m)
{
	if(!vis[m])
	{
		vis[m] = n;
		Ans++;
	}else
	{
		if(vis[m] > n)
		{
			int y = vis[m];
			vis[m] = n;
			if(a[y] == m) dfs(y, b[y]);
		}	
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf ("%d%d", &a[i], &b[i]);
	for (int i = n; i >= 1; --i)
	{
		dfs(i, a[i]);
		ans[i - 1] = Ans;
	}
	for (int i = 0; i < n; ++i)
		printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：qhy_ (赞：1)

### 思路
因为删除牛比较麻烦，所以我们采取从后往前添加牛的方式。

删除牛可能造成一长串连锁反应，而添加牛可以变成让占用了添加的牛的麦片的牛找麦片。
```cpp
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

struct E {
  int c[2], p;  // 喜欢的麦片编号、当前选择的下标
} e[kMaxN];
int a[kMaxN], b[kMaxN];  // 答案、选择每种麦片的奶牛
int n, m;

int main() {  
  ios_base::sync_with_stdio(NULL);
  cin.tie(NULL), cout.tie(NULL);
  //freopen("cereal.in", "r", stdin);
  //freopen("cereal.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].c[0] >> e[i].c[1];
  }
  e[0].p = 2;                            // 初始化判断边界
  for (int i = n, s = 0; i >= 1; i--) {  // 倒序加入奶牛
    for (int j = i; e[j].p < 2;) {       // 不断解决冲突
      int x = e[j].c[e[j].p++];          // 当前奶牛要选的麦片
      if (j < b[x]) {                    // 当前奶牛优先级更高
        swap(b[x], j);                   // 切换选择，继续处理换掉的奶牛
      } else if (!b[x]) {                // 当前麦片未被选择
        b[x] = j;
        s++;  // 增加答案
        break;
      }
    }
    a[i] = s;  // 记录答案
  }
  for (int i = 1; i <= n; i++) {
    cout << a[i] << endl;
  }
  return 0;
}
```

---

## 作者：miao5 (赞：0)

**题目大意：**

有 $n$ 只奶牛，每只都有最喜爱的麦片和次喜爱的麦片，每种麦片只有一袋。

奶牛们排队领麦片，如果有最喜爱的就取走最喜爱的，如果没有最喜爱的但是有次喜爱的就取走次喜爱的。否则就不取麦片。

求在 $[1,n],[2,n],[3,n],...,[n-1,n]$ 每个区间中能有多少只奶牛会取得麦片。

**思路：**

我们**从后往前**遍历每只奶牛，如果奶牛 $i$ 喜欢的麦片没有被取走我们就让 $i$ 取走。如果被取走了我们就看是谁取走的，如果取走它的奶牛**比 $i$ 更靠后**，就把这袋麦片给 $i$ ,让另一只奶牛重新选。

**code:**


```cpp
#include<iostream>
using namespace std;
const int maxn=100004;
int n,m,cnt;
int vis[maxn],res[maxn];
int a[maxn],b[maxn];
void solve(int q){
	int first=a[q],second=b[q];
	if(!vis[first]){  
		++cnt; 
		vis[first]=q; 
		return;  
	}
	if(vis[first]>q){   
		int k=vis[first];   
		vis[first]=q;   
		solve(k);
		return;  
	}
	if(!vis[second]){
		++cnt;
		vis[second]=q;
		return;
	}
	if(vis[second]>q){
		int k=vis[second];
		vis[second]=q;
		solve(k);
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=n;i>0;i--){
		solve(i);
		res[i]=cnt; 
	}
	for(int i=1;i<=n;i++) cout<<res[i]<<endl;
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

这题目还是有意思的。

~~本蒟蒻做了1h才A的。~~

首先这个 $O(n^2)$ 暴力非常显然，

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e5+5;
int n,m,a[INF],b[INF],ans,vis[INF];
signed main()
{
        scanf("%d %d",&n,&m);
        for (int i=1; i<=m; i++) vis[i]=-1;
        for (int i=1; i<=n; i++) scanf("%d %d",&a[i],&b[i]);
        for (int i=0; i<n; i++) {
                ans=0;
                for (int j=i+1; j<=n; j++) {
                        if (vis[a[j]]!=i) {vis[a[j]]=i; ans++;}
                        else if (vis[b[j]]!=i) {vis[b[j]]=i; ans++;}
                }
                cout<<ans<<"\n";
        }
        return 0;
}

```

就是用一个 vis 数组存是否有被取过，然后贪心地验证一下即可，上面那个不用 memset 更节省时间。

这时候，这个代码 30 pts。

复杂度可以优化的地方在于第二个循环，那么怎么优化呢？

首先我们考虑，第一个答案和第二个答案的联系，也就是第一个奶牛被移除对答案的贡献是多少？

思考过后，发现这个好像不太好维护。~~至少本蒟蒻不会。~~ 

于是我就思考到了反向处理，就是说答案可以从尾到头处理。

然后因为这个是当前第一个奶牛，所以必定要满足它的第一个喜好，那么被挤掉的奶牛就会选择第二个喜好。

欸，做到这一步感觉这个还是 $O(n^2)$ 的？其实不然，因为如果有连锁反应的产生，那么前一步就会被另一头奶牛替代。

于是这个操作变成了 $O(1)$ ，而整体的复杂度变成了 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e5+5;
int n,m,a[INF],b[INF],ans[INF],vis[INF],sum,sumff;
signed main()
{
        scanf("%d %d",&n,&m);
        for (int i=1; i<=m; i++) vis[i]=-1;
        for (int i=1; i<=n; i++) scanf("%d %d",&a[i],&b[i]);
        for (int i=n; i>=1; i--) {
                int pre_=-1;
                if (vis[a[i]]!=-1) {pre_=vis[a[i]]; vis[a[i]]=i;}
                else {vis[a[i]]=i; sum++;}
                while (pre_!=-1) {
                        if (vis[b[pre_]]==-1) { vis[b[pre_]]=pre_; pre_=-1; sum++;}
                        else if (vis[b[pre_]]>pre_) {int tmp=pre_; pre_=vis[b[pre_]]; vis[b[tmp]]=tmp;}
                        else pre_=-1;
                        // sumff++;
                }
                ans[i]=sum;
                // cout<<vis[1]<<endl;
        }
        for (int i=1; i<=n; i++) cout<<ans[i]<<"\n";
        // cout<<sumff<<endl;
        return 0;
}

```


---

