# Vova and Trophies

## 题目描述

你现在有 $n$ 枚奖牌，每枚奖牌为金牌或银牌。这些奖牌现在按顺序排成一排。现在你可以调换任意一对奖牌的位置，求金牌最长连续段。

## 样例 #1

### 输入

```
10
GGGSGGGSGG
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4
GGGG
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
SSS
```

### 输出

```
0
```

# 题解

## 作者：Sakura_梦瑶 (赞：4)

可能是我比较菜的缘故,草率地处理边界情况然后提交连wa,
处理出所有情况下的连接段取最大值,在段数<=2的时候特殊判断;
```cpp
#include<bits/stdc++.h>
using namespace std;
int las,now,n,ans,g,p,f=1,c;
struct{int l,r;}a[1001000]; 
int main(){
	cin>>n;for(int i=1;i<=n;i++){
		scanf(" %c",&g);if(g=='S')f++;
		if(g=='G'&&f==1)a[p+1].r=a[p].l;
		if(g=='G'&&f>=1)p++,f=0;
		if(g=='G')a[p].l++;
	}if(p==2&&a[2].r||p==1)cout<<max(a[2].l+a[2].r,a[1].l),exit(0);
	for(int i=1;i<=p;i++)ans=max(ans,a[i].l+a[i].r+1);
	cout<<ans;
}
```

---

## 作者：Ousmane_Dembele (赞：2)

先预处理出来每一位的连续$G$个数，然后再预处理出在开头或结尾是否有跟这个不连续但是仍然是$G$.
```
#include<bits/stdc++.h>
using namespace std;
int n,maxn;
char s[100003];
int a[100003],flag;
bool b[100003];
int main(){
    cin>>n;
    cin>>s+1;
    for(int i=1;i<=n;i++){
        if(s[i]=='G')a[i]=a[i-1]+1,flag=1;
        //123012301234012
        maxn=max(maxn,a[i]);
    }
    if(flag==0){cout<<"0";return 0;}
    for(int i=n-1;i>=1;i--){
        if(a[i]&&a[i+1])
           a[i]=a[i+1];
           
    }
    int f=0;
    for(int i=1;i<=n;i++){
        if(a[i])f=1;
        else if(f==1){
            for(int j=i+1;j<=n;j++)
               b[j]=true;
            break;
        }
    }
    f=0;
    for(int i=n;i>=1;i--){
        if(a[i])f=1;
        else if(f==1){
            for(int j=1;j<=i-1;j++)
               b[j]=true;
            break;
        }
    }
   // for(int i=1;i<=n;i++)
       //cout<<a[i]<<" ";
    for(int i=1;i<=n;i++){
        if(a[i])continue;
        
        if(b[i])maxn=max(maxn,a[i-1]+a[i+1]+1);
        maxn=max(maxn,a[i-1]+a[i+1]);
    }
    cout<<maxn;
}

```

---

## 作者：Dilute (赞：2)

## 瞎搞

首先，我们发现，我们可以把连续一段的金奖杯放在一起计算

同理，我们也把连续一段的银奖杯放在一起计算

那么，我们发现，其实如果两段金奖杯之间的间隔$ > 1$，那么这两段金奖杯是不可能连在一起的

所以，可以得出，仅有两段金奖杯之间的的间隔$=$ 1的时候，它们才有可能并在一起

同时，我们需要考虑单独接一个在上面的情况（我就因为这个被$\color{red}\text{Hacked}$了……）

最后，我们只需要统计$\max$ { $l_i + 1, (l_i + l_{i + 1} + 1) * [gap[i] == 1]$ }即可

但是我们要注意，如果只有两段金奖杯，那么我们是不可能从其他地方搬金奖杯过来填这个间隔的，这个时候它们的金奖杯只能从自己这边拿，所以需要特判一下QwQ

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

int l[100010];
int gap[100010];
char s[100010];

int main(){
    int n = inp();
    scanf("%s", s + 1);
    int cnt = 0;
    int cc = n;
    for(int i = 1; i <= n; i++){
        if(s[i] == 'S'){
            gap[cnt]++;
            cc--;
            continue;
        }
        if(s[i - 1] == 'G')
            l[cnt]++;
        else
            l[++cnt] = 1;
    }
    // printf("%d\n", cnt);
    if(cnt == 0){
        printf("0");
    } else if(cnt == 1){
        printf("%d", l[1]);
    } else if(cnt == 2){
        int ans = std::max(l[1] + 1, l[2] + 1);
        if(gap[1] == 1)
            ans = l[1] + l[2];
        printf("%d", ans);
    } else {
        int ans = 0;
        for(int i = 1; i <= n; i++)
            ans = std::max(ans, l[i] + 1);
        for(int i = 1; i < n; i++)
            if(gap[i] == 1)
                ans = std::max(ans, l[i] + l[i + 1] + 1);
        printf("%d", ans);
    }
}
```



---

## 作者：Jsxts_ (赞：1)

# 题解 CF1082B
[传送门](https://www.luogu.com.cn/problem/CF1082B)

## 题意

你现在有 $n$ 枚奖牌，每枚奖牌为金牌 $(G)$ 或银牌 $(S)$。这些奖牌现在按顺序排成一排。现在你可以调换任意一对奖牌的位置，求金牌的最长连续段。

## 题解

我一看这道题：不就是一个乱搞吗？

然后就调了两个小时，交了一页多。。。

思路：先预处理出每一段连续金牌的数量，每一个银牌隔开两段金牌，最后枚举把相邻两个金牌段连起来形成连续的金牌数量，即

$$ans=max\{a_i+a_{i+1}+1\}(1 \le i <tot)$$

，其中 $tot$ 为金牌的段数。

看起来是不是很简单？但是由于这道题的坑有些多，有很多种情况，所以我调了很久，这些细节在代码里讲。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010],tot;
int main() {
	int n;
	string s;
	cin >> n >> s;
	s = '0' + s;//把字符串补一位 
	int c = 0,cnt = 0;
	for (int i = 1;i <= n;i ++ ) {//预处理连续的金牌段 
		if (s[i] != 'S') c ++;
		else {
			a[++tot] = c,c = 0;
			if (a[tot]) cnt ++;//有金牌的段数要记录，下面要判断 
		}
	}
	a[++tot] = c;//最后一段也要加上 
	if (a[tot]) cnt ++;
	if (cnt == 0) printf("0"),exit(0);//一个金牌都没有 
	if (cnt == 1) {//有一段金牌就输出这一段 
		for (int i = 1;i <= tot;i ++ ) if (a[i]) printf("%d",a[i]),exit(0);
	}
	if (cnt == 2) {//有两段金牌就要分类讨论 
		int mx = 0;
		for (int i = 1;i <= tot;i ++ ) {
			if (a[i] && a[i+1]) {//如果是连着的两段就输出它们的和，不用加1，因为没有其他的金牌段了 
				printf("%d",a[i]+a[i+1]);
				exit(0);
			}
			mx = max(mx,a[i]);//如果不是两段相连，就输出较大的一段个数+1 
		}
		printf("%d",mx+1);
		exit(0);
	}
	int mx = 0;
	for (int i = 1;i < tot;i ++ ) {//其他情况直接计算 
		mx = max(mx,a[i]+a[i+1] + 1);
	}
	printf("%d",mx);
	return 0;
}
```

time ：1.55s，一遍跑到最优解，代码只有 41 行。

---

## 作者：Indigo_Boy (赞：0)

# CF1082B Vova and Trophies 题解

瞎搞题，推荐的，一看是道水题，就随手A了……

## 题目描述
Vova has won $n$trophies in different competitions. Each trophy is either golden or silver. The trophies are arranged in a row.

The beauty of the arrangement is the length of the longest subsegment consisting of golden trophies. Vova wants to swap two trophies (not necessarily adjacent ones) to make the arrangement as beautiful as possible — that means, to maximize the length of the longest such subsegment.

Help Vova! Tell him the maximum possible beauty of the arrangement if he is allowed to do at most one swap.

## 输入格式
The first line contains one integer $n( 2 \le n \le 10^5)$ — the number of trophies.

The second line contains $n$ characters, each of them is either $G$ or $S$. If the $ i -th$ character is $G$, then the $i -th$ trophy is a golden one, otherwise it's a silver trophy.

## 输出格式
Print the maximum possible length of a subsegment of golden trophies, if Vova is allowed to do at most one swap.

## 题解  
**单调队列**  
我的想法是从左往右搞一个前缀和，记录一下当前有几个$G$    
然后我们思考，能让一个$G$去替换$S$的条件是什么:  
是至少有一个$G$没被我们选中，如图  
![](https://img2018.cnblogs.com/blog/1803578/201910/1803578-20191024161945965-1604580127.png)  

想要让倒数第三个格子变成$G$，就必须有一个其他格子是$G$，比如$1$号格子    
那么可以分类讨论一哈子  

1. 如果当前有至少一个$G$没被选中，我们就可以容忍在某一段序列里出现少于等于1个$S$  
![](https://img2018.cnblogs.com/blog/1803578/201910/1803578-20191024162231854-1929590156.png)

如图，绿色是我们已选中的序列，序列外有一$G$，则可以替换  
2.如果当前已选中所有的$G$，那我们就不能从某个地方抽调一个$G$过来替换掉$S$ 
 ![](https://img2018.cnblogs.com/blog/1803578/201910/1803578-20191024162404870-889262309.png)

若为该情况则不可以，因为已经没有多余的$G$来替换了   
那么这个东西的实现我们就可以用一下单调队列  
并不需要真的搞个队列，模拟一下就行  
首先先设一个指针$now$指向零，然后读入  
读入的时候如果读入的是$G$，那么存为$1$，否则存为$0$    
这样前缀和数组$sum[i]$就可以统计出在$i$位置前有多少个$G$  
$sum[i] - sum[now]$就是当前队列里有多少个$G$  
我们比较与$sum[i] - sum[now]$与当前队列里的奖牌数，就可以根据上面说的两种情况做出特判  
大水题……  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int 
int n, a[100010], sum[100010], now, ans, tot;
int main( void ){
	cin >> n;
	char ch;
	for( rint i = 1; i <= n; i++ ){
		cin >> ch;
		if( ch == 'G' ){
			a[i] = 1; tot++;
		} else a[i] = 0;
		sum[i] = sum[i - 1] + a[i];	
	}
	for( rint i = 1; i <= n; i++ ){
		if( sum[i] - sum[now] != tot ){
			while( sum[i] - sum[now] < i - now - 1 && now <= i ) now++; ans = max( ans, i - now );
		}else{
			while( sum[i] - sum[now] < i - now && now <= i ) now++; ans = max( ans, i - now ); 
		}		
	}
	cout << ans;
	return 0;
}
```

~~等等，这东西好像就是单调队列吧2333~~

---

## 作者：vocaloid (赞：0)

枚举。首先明确，由于最多换一对，所以我们要换的只可能是单独的 `S`。于是先预处理。我的做法是对于每个 `S` 将它单独赋值为 $-1$，其他的 `G` 则每块合在一起，记录每块总数，最后记录有多少个 `G` 块。遍历将 `G` 去重后的数组，先将 $ans$ 的初值赋成每个 `G` 块中的最大值，同时如果 `G` 块的总数 $≥2$，这时我们将 $ans+1$ ，毕竟这一次替换不能浪费。然后我们再次遍历这个数组，找到每个单独的 `S` ，先判断这个 `S` 是不是左右都有 `G` 块，如果是那么先将这两个块的总数加起来，赋到临时变量 $res$ ，然后判断一下 `G` 总数是否 $>2$，如果是的话代表替换这个 `S` 的 `G` 不用从旁边的两个块找，$res+1$ ，最后判断 $res$ 与 $ans$ 的关系，更新答案即可。

细节有点多。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],tot,sum,ans;
char ch[100005];
int main()
{
	scanf("%d",&n);
	scanf("%s",ch+1);
	for(int i=1;i<=n;i++)
	{
		if(ch[i]=='S') a[++tot]=-1;
		else if(ch[i]==ch[i-1] && ch[i]=='G') a[tot]++;
		else
		{
			sum++;
			a[++tot]=1;
		}
	}
	for(int i=1;i<=tot;i++) ans=max(ans,a[i]);
	if(sum>=2) ans++;
	for(int i=1;i<=tot;i++)
	{
		if(a[i]==-1 && a[i-1]!=-1 && a[i+1]!=-1)
		{
			int res=a[i-1]+a[i+1];
			if(sum>=2)
			{
				if(sum>2) res++;
				ans=max(ans,res);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：little_sun (赞：0)

# 题解 CF1082B 【Vova and Trophies】

## [安利博客](https://www.cnblogs.com/little-sun0331/p/10046308.html)

$B$比$A$水qwq

这题，对每一个''$G$''，求它这一块的左边界和右边界

然后对于每一个''$S$''，求一下他左边那块的大小，右边那块的大小，再判断一下他能不能把两块连在一起，不能就取大的那块，做完了

```cpp
#include <bits/stdc++.h>

using std::string;

const int MaxN = 100010;

int a[MaxN];
int l[MaxN], r[MaxN];

int main()
{
    int n;
    string s;
    scanf("%d", &n);
    std::cin >> s;
    int len = s.length();
    int sum = 0, ans = 0;
    for (int i = 0; i < len; i++)
        a[i + 1] = s[i] == 'S' ? 0 : 1, sum += a[i + 1];
    if (sum == 0)
        return printf("0") * 0;
    if (sum == n)
        return printf("%d\n", n) * 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 1 && a[i - 1] == 1)
            l[i] = l[i - 1];
        else
            l[i] = i;
    }
    for (int i = n; i >= 1; i--)
    {
        if (a[i] == 1 && a[i + 1] == 1)
            r[i] = r[i + 1];
        else
            r[i] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 0)
        {
            int tmp = 0;
            if (a[i - 1])
                tmp += r[i - 1] - l[i - 1] + 1;
            if (a[i + 1])
                tmp += r[i + 1] - l[i + 1] + 1;
            if(tmp == sum)
                ans = std::max(ans, tmp);
            if (tmp < sum)
                ans = std::max(ans, tmp + 1);
            if (a[i - 1] && r[i - 1] - l[i - 1] + 1 < sum)
                ans = std::max(r[i - 1] - l[i - 1] + 2, ans);
            if (a[i + 1] && r[i + 1] - l[i + 1] + 1 < sum)
                ans = std::max(r[i + 1] - l[i + 1] + 2, ans);
            
        }
    }
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：Zechariah (赞：0)

怎么蓝了（你谷日常乱评分）  
题意就是换掉一个S，使得最多的连续的G个数最多  
所以可以枚举每一个S尝试换掉，计算此时的答案，取最大值就行了  
换之前先预处理一下，把所有连续的G找出来编上号，并统计个数  
换的时候分情况讨论：
1.当前有2个以上的连续的G段，由于我们只能换一个S，所以最多也就是把两个连续的G段拼在一起，如果有两个以上的连续的G，当然是把别的G和当前S换最优啦  
2.有两个连续的G段，这时候如果两个G段比较远，那么答案就为两个G段中的较大值+1，否则为这两个G段的和  
3.只有一个G段，直接就是答案
```
#include <bits/stdc++.h>
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
const int N = 1e5 + 10;
using namespace std;
namespace fast_IO {
	long long read()
	{
		register long long num = 0;
		register char ch;
		register bool flag = false;
		while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
		if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
		while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
			num = (num << 1) + (num << 3) + (ch ^ 48);
		if (flag)return -num; return num;
	}
	void write(register long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
	int max(register int a, register int b) { if (a > b)return a; return b; }
	int min(register int a, register int b) { if (a < b)return a; return b; }
};
char s[N];
int cnt[N], belong[N], tot;

int main()
{
	register int n = fast_IO::read();
	register int sum = 0, ans = 0;
	scanf("%s", s + 1);
	for (register int i = 1; i <= n; ++i)
	{
		if (s[i] == 'G')
			if (s[i - 1] == 'G')++cnt[belong[i] = belong[i - 1]];
			else cnt[belong[i] = ++tot] = 1;
	}
	for (register int i = 1; i <= n; ++i)
	{
		if (s[i] == 'G')continue;
		if (tot > 2)ans = fast_IO::max(ans, cnt[belong[i - 1]] + cnt[belong[i + 1]] + 1);
		else if (tot == 2)ans = fast_IO::max(ans, fast_IO::max(fast_IO::max(cnt[belong[i - 1]] + 1, cnt[belong[i + 1]] + 1), cnt[belong[i - 1]] + cnt[belong[i + 1]]));
		else ans = fast_IO::max(ans, fast_IO::max(cnt[belong[i + 1]], cnt[belong[i - 1]]));
	}
	ans = fast_IO::max(ans, cnt[belong[n]]);
	fast_IO::write(ans);
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：0)

分类讨论一下。

如果一段奖牌全都是金牌，那么直接用这段奖牌的数量来更新答案即可。

如果是两段金牌中间夹了一块银牌 **并且** 在这两段金牌之外还有多余的金牌，那么我们就把中间这块银牌与多余的金牌交换位置，从而把两段金牌拼起来更新答案。

其他情况的话就不能更新答案了。

实现的话可以用前缀和快速求出一段金牌的数量，双指针扫一遍就行了。

核心代码：

```cpp
const int N=2e5+10;
int n,s[N],ans;//s为前缀和数组
char a[N];
signed main()
{
	cin>>n>>a+1;
	for(ri int i=1;i<=n;++i)
		s[i]=s[i-1]+(a[i]=='G');
	ri int l=1,r=1;
	while(r<=n)
	{
		while(s[r]-s[l-1]+1<r-l+1) ++l;//如果区间[l,r]之间银牌数量大于1显然是不合法的
		if(s[r]-s[l-1]+1==r-l+1&&s[n]-s[r]+s[l-1]-s[0])
			ans=max(ans,r-l+1);//两段金牌中间夹银牌的情况
		else if(s[r]-s[l-1]==r-l+1) ans=max(ans,r-l+1);//一段金牌的情况
		++r;
	}
	cout<<ans;
	return 0;
}
```

---

