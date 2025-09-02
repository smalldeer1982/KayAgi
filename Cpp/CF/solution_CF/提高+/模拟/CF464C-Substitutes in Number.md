# Substitutes in Number

## 题目描述

### 题意
有一个由数字组成的字符串$s$和$n$条指令$d_i->t_i$。意思是用$t_i$替换所有字符串中的$d_i$。例如，如果$s=123123$，则“2→00”将把$s$转换为$10031003$，查询“3→”(用空字符串替换$3$),将$s$转换为$s=1212$。在所有的指令之后，请在十进制数等于$s$的情况下取模$mod=1000000007(10^9+7)$。

同时**需要注意，在$s$表示为十进制数时，需要忽略前导$0$；如果$s$是一个空字符串，那么就默认为$0$**。

-------

## 样例 #1

### 输入

```
123123
1
2-&gt;00
```

### 输出

```
10031003
```

## 样例 #2

### 输入

```
123123
1
3-&gt;
```

### 输出

```
1212
```

## 样例 #3

### 输入

```
222
2
2-&gt;0
0-&gt;7
```

### 输出

```
777
```

## 样例 #4

### 输入

```
1000000008
0
```

### 输出

```
1
```

# 题解

## 作者：Jsxts_ (赞：5)

这道题是一道类似 DP 的题。

我们发现，这个答案我们是不可能用数存下来的，位数很大，只能考虑转化。

因为 $(a+b)\%mod=(a\%mod+b\%mod)\%mod$，所以我们可以考虑将每一位分解出来单独算，最后拼在一起。

接下来是 DP 的思路。我们定义 $d_i$ 为数字 $i$ 经过转化后的位数（这里因为方便，$d_i$ 直接表示 10 的（位数 $-1$ ）次幂对 $10^9+7$ 取模的值），拼成一个数时可以直接用。$b_i$ 表示数字 $i$ 转化后的数（同样对 $10^9+7$ 取模）。这样，我们可以在表示这个数时用拼数的办法表示，也可以在最终答案里拼出来，细节见代码。

因为这道题还有多次的处理，所以我们要考虑顺序先后。由于原本的操作是后面覆盖前面，所以倒着做就可以保证后面影响前面。

还有读入等细节都在注释里说明。

AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
string s,s2[100010];
int a[100010];
ll d[10],b[10];
int main() {
	int n;
	cin >> s >> n;
	for (int i = 1;i <= n;i ++ ) {
		scanf("%d",&a[i]);//先读入数字
		string ss;
		cin >> ss;
		s2[i] = ss.substr(2);//过滤空格
	}
	for (int i = 0;i <= 9;i ++ ) d[i] = 10, b[i] = i;//初始化位数为1（10^1），转成的数就是它本身
	for (int i = n;i;i -- ) {//从后往前算
		int sz = s2[i].size();
		if (!sz) {//当转成空数（样例2）时
			b[a[i]] = 0;
			d[a[i]] = 1;//位数为0（10^0）
			continue;
		}
		ll num = 0,nd = 1;//记得开 long long
		for (int j = 0;j < sz;j ++ ) {
			int x = s2[i][j] - '0';
			num = (num * d[x] + b[x]) % mod;//乘上 d[x] 再加上 b[x] 就可以把这个数拼上去（可以自己模拟一下）
			nd = (nd * d[x]) % mod;//新的位数
		}
		b[a[i]] = num;
		d[a[i]] = nd;
	}
	ll ans = 0;
	for (int i = 0;i < s.size();i ++ ) {
		int x = s[i] - '0';
		ans = (ans * d[x] + b[x]) % mod;//依然是拼起来
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：liuyifan (赞：2)

##  同余定理+模拟
### 1.思路
首先我们可得同余定理使用后不能再修改数字。
那么为了让同余定理能被使用，我们将每个数字倒序处理，这样就能使用同余定理了。
### 2.解法
记录每个数字实际代表的数字和实际对应的位数。
然后倒序处理上来即可。
### 3.code（拒绝抄袭,共建和谐洛谷）
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define reg register //register卡常 
#define ll long long
#define y1 liuifan_y1 
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f 
#define data liuyifan_data //防止撞关键字 
#define next liuyifan_next 
#define ture true //防止单词打错 
#define flase false 
#define lowbit(x) x&(-x)
#define mod (ll)(pow(10,9)+7)//定义模数 
using namespace std;
char s[100005],t[100005];
class node
{
	public://=struct 
		int d;
		string s;
}a[100005];
ll v[100005],w[100005],d[100005],n,x,now,len,ans;//在确保不会MLE的情况下多开一点更保险 
inline ll wei(ll x)
{
	if(x==0)return 1;//特判0 
	reg ll ans=0;
	while(x)x/=10,ans++;//模拟 
	return ans;//求一个整数的位数 
}
inline void solve()
{
	scanf("%lld",&n);
	getchar();//过滤回车 
	for(reg int i=1;i<=n;i++)
	{
		scanf("%d->",&a[i].d);//按指定格式scanf,如本行 
		gets(t);//将一整行读入t(包括空格和tab,不包括行末回车) 
		a[i].s=t;
	}
	for(reg int i=0;i<10;i++)v[i]=i,w[i]=10;
	for(reg int i=n;i>=1;i--)
	{
		now=0;
		len=a[i].s.length();
		if(len==0)
		{ 
			v[a[i].d]=0;
			w[a[i].d]=1;
			continue;
		}//字符串为空,特殊处理 
		x=1;
		for(reg int j=0;j<len;j++)
		{
			now*=w[a[i].s[j]-'0'];
			now+=v[a[i].s[j]-'0'];
			x=(x*w[a[i].s[j]-'0'])%mod;
			now%=mod;//记得取模,思路上面有 
		}
		v[a[i].d]=now;
		w[a[i].d]=x;
	}
	ans=0;//记得每次调用前重置 
	for(reg int i=0;s[i];i++)
	{
		ans*=w[s[i]-'0'];
		ans+=v[s[i]-'0'];
		ans%=mod;
	}
	printf("%d\n",ans);
}
int main()
{	
	while(gets(s))solve();
	return 0;
}
```
### 4.样例说明
本题的正确样例输入:
```cpp
/*本题的一些样例(题面样例格式有问题)，输出以题面为准
123123
1
2->00

123123
1
3->

222
2
2->0
0->7

1000000008
0
*/
```

---

## 作者：ivyjiao (赞：0)

没有 dsfz 的学长来水题解吗 qwq？

显然不能直接存储数字，不然 TLE 并且 MLE。

考虑 dp，我们从后往前 dp，让后面的操作覆盖前面的操作。

那么设 $b_i$ 为数字 $i$ 目前需要被转成哪个数字，$d_i$ 为数字 $i$ 目前被转成的数字的位数（这里为了方便乘，用 $10$ 的位数次方表示）。

初值就是 $b_i=i,d_i=10$。

那么一次操作处理时，对于新数，就可以用拼数的方式表示出来（注意随时取模），最后的答案自然也可以用拼数的方式表示出来。

$b$ 和 $d$ 更新的式子不会写，类似快读的式子，具体的看代码吧。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1e9+7,N=1e5+1;
int n,a[N],d[10],b[10],ans;
string t,s[N];
signed main(){
    cin>>t>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>s[i];
        s[i]=s[i].substr(2);
    }
    for(int i=0;i<=9;i++) d[i]=10,b[i]=i;
    for(int i=n;i;i--){
		if(!s[i].size()){
			b[a[i]]=0;
			d[a[i]]=1;
			continue;
		}
        int cnt=0,wei=1;
        for(int j=0;j<s[i].size();j++){
            int x=s[i][j]-'0';
            cnt=(cnt*d[x]+b[x])%p;
            wei=wei*d[x]%p;
        }
        b[a[i]]=cnt;
        d[a[i]]=wei;
    }
    for(int i=0;i<t.size();i++){
        int x=t[i]-'0';
        ans=(ans*d[x]+b[x])%p;
    }
    cout<<ans;
}
```

---

