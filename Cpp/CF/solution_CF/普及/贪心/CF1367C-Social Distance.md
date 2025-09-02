# Social Distance

## 题目描述

Polycarp and his friends want to visit a new restaurant. The restaurant has $ n $ tables arranged along a straight line. People are already sitting at some tables. The tables are numbered from $ 1 $ to $ n $ in the order from left to right. The state of the restaurant is described by a string of length $ n $ which contains characters "1" (the table is occupied) and "0" (the table is empty).

Restaurant rules prohibit people to sit at a distance of $ k $ or less from each other. That is, if a person sits at the table number $ i $ , then all tables with numbers from $ i-k $ to $ i+k $ (except for the $ i $ -th) should be free. In other words, the absolute difference of the numbers of any two occupied tables must be strictly greater than $ k $ .

For example, if $ n=8 $ and $ k=2 $ , then:

- strings "10010001", "10000010", "00000000", "00100000" satisfy the rules of the restaurant;
- strings "10100100", "10011001", "11111111" do not satisfy to the rules of the restaurant, since each of them has a pair of "1" with a distance less than or equal to $ k=2 $ .

In particular, if the state of the restaurant is described by a string without "1" or a string with one "1", then the requirement of the restaurant is satisfied.

You are given a binary string $ s $ that describes the current state of the restaurant. It is guaranteed that the rules of the restaurant are satisfied for the string $ s $ .

Find the maximum number of free tables that you can occupy so as not to violate the rules of the restaurant. Formally, what is the maximum number of "0" that can be replaced by "1" such that the requirement will still be satisfied?

For example, if $ n=6 $ , $ k=1 $ , $ s= $ "100010", then the answer to the problem will be $ 1 $ , since only the table at position $ 3 $ can be occupied such that the rules are still satisfied.

## 说明/提示

The first test case is explained in the statement.

In the second test case, the answer is $ 2 $ , since you can choose the first and the sixth table.

In the third test case, you cannot take any free table without violating the rules of the restaurant.

## 样例 #1

### 输入

```
6
6 1
100010
6 2
000000
5 1
10101
3 1
001
2 2
00
1 1
0```

### 输出

```
1
2
0
1
1
1```

# 题解

## 作者：registerGen (赞：4)

# Solution

我分了好几类，可能有一些类是不用分的。

若 $s$ 是全 $0$ 串，则：

![tmp.png](https://i.loli.net/2020/06/17/2FNhx8tuLVKIgaG.png)

黑色的表示可以坐人。

答案为 $1+\left\lfloor\dfrac{n-1}{k+1}\right\rfloor$。

否则，把 $s$ 分成若干块，每块都是全 $0$ 串，考虑每个块的大小 $x$。

若这个块不在 $s$ 的两端，则：

![tmp.png](https://i.loli.net/2020/06/17/HRLGgocQ3hN6vX4.png)

答案为 $\left\lfloor\dfrac{x-k}{k+1}\right\rfloor$。

若这个块在 $s$ 的两端，则：（以在左端点为例）

![tmp.png](https://i.loli.net/2020/06/17/RbkotTxpd9NGCEH.png)

答案为 $\left\lfloor\dfrac{x}{k+1}\right\rfloor$。

最后把每个块的答案加一下就好了。

# Code

其实建议自己写，因为我的屑代码应该可以精简一下qwq

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

const int N=2e5;

int a[N+10],n,k;
int cnt[N+10],totc;

inline void work()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%1d",a+i);
	bool f=1;
	for(int i=1;i<=n;i++)
		if(a[i]==1)
		{
			f=0;
			break;
		}
	if(f==1)
	{
		printf("%d\n",1+(n-1)/(k+1));
		return;
	}
	int _cnt=0;totc=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0)_cnt++;
		else if(_cnt)cnt[++totc]=_cnt,_cnt=0;
	}
	cnt[++totc]=_cnt;
	int ans=0;
	for(int i=1;i<=totc;i++)
	{
		int x=cnt[i];
		if((i==1&&a[1]==0)||(i==totc&&a[n]==0))
		{
			ans+=x/(k+1);
			continue;
		}
		if(x<2*k+1)continue;
		else ans+=(x-k)/(k+1);
	}
	printf("%d\n",ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
```

---

## 作者：LeavingZzz (赞：4)

# Solution For CF1367C  
本题直接模拟  
对于每一个串，做一次前缀和。  
那么现在对于两个下标 $i,j$ 如果满足 $sum[i]==sum[j]$ 那么说明 $i,j$ 之间没有 $1$。  

单独开一个变量记录从左往右的时候，上一个 $1$ 的下标，这样就解决了左边的相邻 $1$，对于右边相邻的 $1$，直接判断 $sum[i]$ 和 $sum[i+k]$ 的关系来确定是不是有 $1$ 在中间。  

也就是说，从左往右枚举的时候，只要该位置能变成 $1$ 就一定变，这样一定是最优的。  

之所以没有用判断前缀和是否相等的方法来确定左边相邻的 $1$ 是因为负数下标不好处理，而对于右边的 $1$ 这样判断就只用把数组开大一倍（保证 $i+k$ 不越界）。  

时间复杂度 $O(tn)$  

$\large\mathsf{Code:}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<set>
using namespace std;
typedef long long LL;
const int maxn=200007;
int T;
int N,k;
inline int R()
{
	char c;
	int re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
char s[maxn<<1];
int sum[maxn<<1];
int main()
{
	T=R();
	while(T--)
	{
		N=R();k=R();
		memset(sum,0,sizeof(sum));
		memset(s,0,sizeof(s));//这个要置零！（没清零罚时了/kk）
		scanf("%s",s+1);
		for(register int i=1;i<=2*N;i++)
			sum[i]=sum[i-1]+(s[i]=='1');
		int last=-k-1,ans=0;//注意last的初始化
		for(register int i=1;i<=N;i++)
		{
			if(s[i]=='1') last=i;
			if(i-last>k&&sum[i+k]==sum[i]) ++ans,last=i;//此地可以变成1，记录位置，更新答案
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
~~萌新上分，越上越昏~~  
$\huge\mathcal{The\text{ }End}$  
蟹蟹管理大大审核^_^

---

## 作者：追梦之鲸 (赞：3)

本蒟蒻的第$015$篇题解。

[经典回顾CF1367C](https://www.luogu.com.cn/problem/CF1367C)

### 2021 05-29 18:48:25 纪念最优解

### 思路

本蒟蒻的做法是加了优化的暴力。

从 $a_1$ 开始枚举，如果为$1$那就让 $i+s$（因为 $a_i$ 是$1$的话，那么附近 $a_{i-s}$到$a_{i+s}$都不能变成$1$，我们只考虑后面的位置，所以让 $i+s$）如果这个地方能放的话，我们就把答案加一，然后 $i+s$（道理同上）。

那么问题来了，怎么判断这个地方能不能放呢？我选择的是使用前缀和，判断的时候只要看看 $B_i$ 是否等于 $\huge{B_{\min (i+k,n)}}$ （注意是 $\min (i+k,n)$ 不然的话没清零可能会出错，自己想想为什么）就行了（$B$ 数组为前缀和数组）。



### Code：
```c
#include<bits/stdc++.h>
#define ri register
#define FOR(iee,eei,eie) for(iee=eei;iee<=eie;iee++)
//本人码风有问题，请见谅QwQ
using namespace std;
template <class T>
inline void read(T &x) {//快读
    x = 0;
    ri char c = getchar();
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
}
bool a[200010];
int b[200010];
int t,n,k,ans;

int main()
{
    read(t);
    int i;
    while(t--)
    {
        read(n);read(k);
        FOR(i,1,n)
        {
            scanf("%1d",&a[i]);
            if(a[i])
                b[i]=1;//处理前缀和
            b[i]+=b[i-1];
        }
        FOR(i,1,n)
        {//循环主体
            if(a[i])
            {
                i+=k;
                continue;
            }
            if(b[i]==b[min(i+k,n)])
            {
                ans++;
                i+=k;
            } 
        }
        FOR(i,1,n)b[i]=0;//这里我设了双重保险，有备无患
        printf("%d\n",ans);
        ans=0;//记得清零！！！
    }
    return 0;
}
```

$$\text{时间复杂度 O(tn)}$$

最后蟹蟹管理大大的审核Orz

---

## 作者：Werner_Yin (赞：3)

## 题意
给出长度为 $n$ 的只包括 $0$ ,$1$ 的字符串 $s$ ,要求 两个 $1$ 中间至少有 $k$ 个 $0$ ，请求出最多可以将多少个 $ 0 $ 变成 $1$ 。输入的字符串保证合法。
## 思路
我们注意到原题有这样一句话：

The sum of n for all test cases in one test does not exceed $2\cdot 10^5$ .

数据范围还行，可以暴力扫描过。

我们可以循环遍历 $s$ ,当在第 $i$ 位时，我们可以找一下它前面最近的 $1$ 在哪儿，后面最近的 $1$ 在哪儿，然后判断这里可不可以换成 $1$ ,如果可以，我们就能修改一下当前字符串并且 $ans++$ 。

我们可以再优化一下，记录每个 $1$ 出现的位置，这样在循环时就不要暴力去找了。但要注意前面没有 $1$ 和后面没有 $1$ 的情况。

## 代码

```cpp
#include<bits/stdc++.h>
#define mes(x) memset(x,0,sizeof(x))
using namespace std;
template <typename T>
void re(T &x){
	#define ge getchar() 
	x=0;int sgn=1;char ch=ge;
	for(;!isdigit(ch);ch=ge) if(ch=='-') sgn=-1;
	for(;isdigit(ch);ch=ge) x=(x<<1)+(x<<3)+(ch^48);
	x*=sgn;
}
template <typename T>
void write(T x){
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	int k=0,que[20];
	while(x>0){
		que[++k]=x%10;
		x/=10;
	}
	for(int i=k;i>0;i--) putchar(que[i]+48);
	putchar('\n');
	return;
}
const int MAXN=2e5+10;
int main (){
	int T;
	re(T);
	while(T--){
		int ans=0,n,k,a[MAXN],le=0,las=0,nxt=1;
  /* a: 每个 1的位置，
  	le: a 的长度
   las:在扫描过程中上一个是 1的位置
   nxt: a[nxt]代表 下一个是 1的位置
   ans: answer
  */
		mes(a);
		re(n);re(k);
		for(int i=1;i<=n;i++){
			int tem;
			scanf("%1d",&tem);//一位一位数字读入
			if(tem) a[++le]=i;
		}
		for(int i=1;i<=n;i++){
			if(i==a[nxt]) {nxt++;las=i;continue;}
        //如果 第i 位已经是 1（也就是a[nxt]==i) 跳过到下一位
			if(i>a[nxt])nxt++; //这种情况应该可以忽略，但为了爆零还是写一下
			if(las==0||i-las>k){
           //判断前面有没有至少 k 个 0，这里要注意可能前面没有1的判断
				if(nxt>le||a[nxt]-i>k){
           //判断后面有没有至少 k 个 0，这里要注意可能后面无1的判断
					ans++;
					las=i;
				}
			}
		}
		write(ans);
	}
	return 0;
}
```


---

## 作者：45dino (赞：1)

比想象中的略复杂，或许可以改成绿题？

直接存每个 $1$ 的坐标，计算两个 $1$ 之间可以再放多少个 $1$ 。

要单调计算第一个 $1$ 前面和最后一个 $1$ 后面的情况。

还要特判开始时没有 $1$ 的情况。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int t,n,k;
string s;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		v.clear();
		int ans=0;
		scanf("%d%d",&n,&k);
		cin>>s;
		for(int i=0;i<s.size();i++)
			if(s[i]=='1')
				v.push_back(i+1);
		if(v.size()==0)
		{
			if(n%(k+1)==0)
				cout<<n/(k+1)<<endl;
			else
				cout<<n/(k+1)+1<<endl;
			continue;
		}
		for(int i=1;i<=v[0];i+=(k+1))
			ans++;
		for(int i=0;i<v.size()-1;i++)
			ans+=max(v[i+1]-v[i]-1-k,0)/(k+1);
		for(int i=v[v.size()-1];i<=n;i+=(k+1))
			ans++;
		cout<<ans-2<<endl; 
	}
	return 0;
}
```


---

## 作者：furina_1013 (赞：0)

前置芝士：
请学习以下芝士片。

[前缀和](https://www.luogu.com.cn/article/7qe3pqis)。

  ### 题意详解
有一个长度为 $n$ 的仅含 $0$,$1$ 字符串（注意不是数列！）与一个整数 $k$ 表示每两个 $1$ 之间的最小间隔。

我们可以将一个 $0$ 改为 $1$ ，但要让每两个 $1$ 之间有 $k$ 的间隔。

问最多能改变多少个？

### 思路讲解
emm...看见最大，优先考虑**贪心思想** 。

既每 $k$ 个连续的 $0$ 两端必各有一个 $1$。

脑中第一个想起了 ~暴力~ ，本题暴力的时间复杂度为 $O_{(nt)}$
最大为 $2 \times 10^9$ **必定超时**。

考虑优化一下：找到可以改变的位置后，直接让**计数器加等** $k$。 

但是，如果当前位置为 $1$ 又该如何判断呢？
直接循环未免太浪费时间，可以用前缀和进行二次优化。

思路讲述完毕。

最好加上读写优化，因为数据量过大。



### code：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int k;
int fu[200005];//原数组
int furina[200005];//前缀和数组
int ans;
int main()
{
  	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int i=1;i<=t;i++)	//t组样例
	{
		ans=0;
		//数组无需初始化为0，原先的会覆盖掉他
		cin>>n>>k;
		for(int j=1;j<=n;j++)
		{
			char a;
			cin>>a;
			fu[j]=a -'0';
			furina[j]=furina[j-1]+fu[j];
		}
		//读入原数组，并生成前缀和
		for(int j=1;j<=n;j++)//遍历原数组
		{
			if(fu[j]==1)
			{
				j+=k;
			}//当第j位有1时，则j+k-1位内不可改变为1
			else 
			{
				if(j+k<=n)
				{
					if(furina[j]==0 && furina[j+k]==0  )
					{
						//前缀和第i位与i+k位相等，则可以改变
						//判断i+k是否小于n，是为了判断是否越界，因为数组并没有初始化，会导致奇怪的答案
						ans++;//累加答案
						j+=k;//同样的，j+k-1的范围内不会能有改变得数
					}
				}
				else
				{
					if(furina[j]==0 && furina[n]==0  )
					{
						ans++;//累加答案
						j+=k;//同样的，j+k-1的范围内不会能有改变得数
					}
				}
				
			}	
		}
		cout<<ans<<"\n";//这个相较于endl更快

	}
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# CF1367C Social Distance 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1367C)

### 分析

考虑暴力放 `1`，在遇到下一个 `1` 的时候检查上一个放的是否符合条件。

如果符合，则不做更改；反之记录的答案减 $1$ 即可。

这里用一个记录变量来记录上一个 $1$ 的位置，如果发现这个位置已经能放，则在这个位置放，记录位置，再重复过程直到需要检查。

这里非常显然，早放比晚放更优，所以可以这样贪心。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int t,n,k,las,ans,fi,la;
string s;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>s;
		las=fi=-5e5;
		ans=0;
		for(int i=0;i<n;i++){
			if(s[i]=='1'){
				if(i-las<=k){
					ans--;
				}
				las=i;
			}
			if(i-las>k&&s[i]=='0'){
				las=i;
				ans++;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：__int127 (赞：0)

## CF1367C Social Distance 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1367C)

### 题目大意

本题有多组数据。

给出一个长为 $n$ 的 $01$ 字符串 $a$ 和一个正整数 $k$，你可以进行若干次操作，对于每次操作，你可以将 $a_i$ 变成 $1$，所有操作完成后，需保证每个 $a_i$ 和 $a_j$（$a_i=1,a_j=1$），它们之间的距离 $\ge k$（定义距离为 $a_i$ 和 $a_j$ 之间的数的个数，不包含 $a_i$ 和 $a_j$），输出最多操作次数。

$1\le k\le n\le2\times10^5,a_i\in{\{0,1\}}$。

### 思路

首先，众所周知，只要能将 $a_i$ 变成 $1$，就把它改变，但实际上我们是记录操作次数，不需要把它改变，只要将操作次数变量加 $1$ 就行，现在我们就需要知道如何判断是否能将 $a_i$ 变成 $1$。

我们可以在遍历 $a$ 的时候如果遇到 $1$，就将 $i$ 加 $k$，因为 $a_i$ 已经为 $1$，它右边 $k$ 个距离都一定无法改变数字。如果 $a_i=0$，那么就看它的左右 $k$ 个距离是否有 $1$，当然不能盲目遍历，这样会 TLE，我们可以用前缀和来解决。

可以用前缀和数组 $sum$ 存入 $a_1\sim a_i$ 之间 $1$ 的个数，只要 $sum_{\min(i+k,n)}-sum_{i-1}=0$（其中 $sum_{\min(i+k,n)}$ 是为了防止数组越界），就说明 $a_i$ 右边的 $k$ 个距离都没有 $1$，并将 $i$ 加 $k$，因为 $a_i$ 已经变为 $1$，也就是说，$a_i$ 可以将 $0$ 变成 $1$。但这时有人就说了，还没有判断左边呢，其实不用判断左边，因为当遇到 $1$ 时，已经将 $i$ 加 $k$，也就是 $a_i=0$ 时，$a_{max(1,i-k)}\sim a_i$（其中 $a_{max(1,i-k)}$ 是为了防止数组越界）一定都为 $0$。

这样就可以写代码了。

### 代码+注释

很短的代码，只有 $20$ 行。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k, a[200005], sum[200005], gs;
char c;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	// 关闭读写同步
	cin >> t;// t 组数据
	while (t--){
		cin >> n >> k;
		for (int i = 1; i <= n; i++){
			cin >> c;
			a[i] = c - '0';// 存入 a 数组
			sum[i] = sum[i - 1] + a[i];// 生成前缀和数组
		}
		for (int i = 1; i <= n; i++){
			if (a[i] == 1){// 为 1 的情况
				i += k;
			} else {// 为 0 的情况
				if (sum[i] == sum[min(i + k, n)]){
					gs++;
					i += k;
				}
			}
		}
		cout << gs << "\n";// 输出并换行
		gs = 0;// 重置操作个数（即 gs）变量
	}
	return 0;
}
```

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：mot1ve (赞：0)

这题显然 $nlogn$ 可过，那么就没什么思维难度了。先把所有是1的位置存下来，对于每一个位置，通过二分查找确定离他最近的一个1的位置，看距离满不满足就OK了。

```
//nlogn 
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int n,k,T,ans;
int a[20000010];//转成int类型 
vector<int> g;//记录1的位置 
int main()
{
    cin>>T;
    while(T--)
    {
        ans=0;
        cin>>n>>k;
        string s;
        cin>>s; 
        g.clear();
        //先把所有1的位置记录下来，然后O(n)+二分扫 
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='1')
            g.push_back(i);
            a[i]=(s[i]-'0');
        }
        g.push_back(INF);
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='0')
            {
                int p=upper_bound(g.begin(),g.end(),i)-g.begin();
                if(p==g.size())
                {
                    i+=k;
                    ans++;
                    continue;
                }
                if(g[p]-i-1>=k)//距离大于等于k，可以坐
                {
                    i+=k;
                    ans++;
                } 
            }
            else if(s[i]=='1')
            {
                i+=k;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
} 
```

---

