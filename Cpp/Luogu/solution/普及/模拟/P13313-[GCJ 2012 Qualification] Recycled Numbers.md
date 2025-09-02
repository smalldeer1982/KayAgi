# [GCJ 2012 Qualification] Recycled Numbers

## 题目描述

你是否曾因电视节目总是反复播放相同内容而感到烦躁？其实我对电视并不在意，但有时我会对数字也有类似的感觉。

我们称一对不同的正整数 $(n, m)$ 为**可循环对**，如果你可以通过把 $n$ 的后面若干位数字移到最前面（且不改变这些数字的顺序）得到 $m$。例如，$(12345, 34512)$ 是一个可循环对，因为你可以把 $12345$ 的末尾 $345$ 移到最前面，得到 $34512$。注意，$n$ 和 $m$ 必须位数相同，且都不能有前导零。

给定两个整数 $A$ 和 $B$，它们具有相同的位数且都没有前导零。请问有多少不同的可循环对 $(n, m)$ 满足 $A \leqslant n < m \leqslant B$？


## 说明/提示

**我们确定第 4 组样例的输出吗？**

是的，我们确定第 4 组样例的输出为 287。

**限制条件**

- $1 \leq T \leq 50$
- $A$ 和 $B$ 的位数相同

**测试集 1（10 分，可见结果）**

- $1 \leq A \leq B \leq 1000$

**测试集 2（15 分，隐藏结果）**

- $1 \leq A \leq B \leq 2000000$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
1 9
10 40
100 500
1111 2222```

### 输出

```
Case #1: 0
Case #2: 3
Case #3: 156
Case #4: 287```

# 题解

## 作者：Temp113 (赞：3)

## Solution

枚举即可。

枚举数 $x$ 移动的位置，得到数 $y$，特殊判断 $y$ 与 $x$ 是否相同（例如 $x = 11$），及 $x$ 是否已经匹配 $y$（例如 $x = 2121$）。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 10, M = 2000005;
int t, a, b, ans;
int g[N], numg, gg[N], numgg;
int tp, tp2;
bool flg[M];
vector<int> V;
inline void solve(){
	ans = 0;
	cin >> a >> b;
	for(int i = a; i <= b; i++){
		tp = i;
		numg = 0;
		while(tp){
			g[++numg] = tp % 10;
			tp /= 10;
		}
		reverse(g + 1, g + numg + 1);
		V.clear();
		for(int j = 1; j <= numg; j++){
			numgg = tp2 = 0;
			for(int p = j; p <= numg; p++) gg[++numgg] = g[p];
			for(int p = 1; p <= j - 1; p++) gg[++numgg] = g[p];
			for(int p = 1; p <= numgg; p++) tp2 = tp2 * 10 + gg[p];
			if(tp2 >= a && tp2 <= b && tp2 != i && !flg[tp2]){
				flg[tp2] = 1;
				V.push_back(tp2);
				ans++;
			}
		}
		for(auto &v : V) flg[v] = 0;
	}
	cout << ans / 2 << '\n';
	return ;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> t;
	for(int kk = 1; kk <= t; kk++){
		cout << "Case #" << kk << ": ";
		solve();
	}
	return 0;
}
```

---

## 作者：qwqTNTqwq (赞：3)

[题目Link](https://www.luogu.com.cn/problem/P13313)
## 思路
每次从 $a$ 到 $b$ 枚举，每次将数字的最后一位移到前面，判断是否满足条件，如果满足将数对数量加一，不断重复直到发现与前面数字相同，然后换下一个数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    int count = 1; //记录测试用例编号。
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        int cnt = 1, a1 = a;
        while (a1 >= 10) //计算数位。
        {
            cnt *= 10;
            a1 /= 10;
        }
        int ans = 0;
        for (int n = a; n <= b; n++) //枚举从a到b的所有数字。
        {
            int tmp = n;
            while (1) 
            {
                tmp = (tmp / 10) + ((tmp % 10) * cnt); //每次将数字最末尾的一个数字，移到最前面。
                if (tmp == n) //如果重复就退出循环，换下一个数。
                {
                    break;
                }
                if (tmp > n && tmp <= b) //如果移动后的数字满足条件。
                {
                    ans++; //数对数量加一。
                }
            }
        }
        cout << "Case #" << count++ << ": " << ans << endl; //输出格式要与题目保持一致。
    }
    return 0;
}
```
update：修改了错误的代码。

---

## 作者：IkillDream (赞：3)

# P13313 题解

## 前言

这其实就是一道~~简单~~的枚举题。

这题的数据范围可真奇怪？

## 思路

我们只需要枚举 $n$ 在区间 $[A,B]$ 内，生成所有可能的循环移位数字，然后查询每个生成的数字，检查其是否满足 $n < m \le B$，并且 $m$ 是 $n$ 的循环移位，最后一定要注意一下**去重**。

## [AC](https://www.luogu.com.cn/record/225255164) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int vis[10000005],num[105];
int main(){
	int t,a,b,ans,kkk01,kkk02,kkk03,kkk04,kkk05;
	cin>>t;
	for(int kkk01=1;kkk01<=t;kkk01++){
		cin>>a>>b;
		ans=0;
		memset(vis,0,sizeof(vis));
		for(int n=a;n<=b;n++){
			int len=0,tmp=n;
			while(tmp) num[len++]=tmp%10,tmp/=10;
			reverse(num,num+len);
			for(int i=1;i<len;i++){
				int m=0;
				for(int j=i;j<len;j++) m=m*10+num[j];
				for(int j=0;j<i;j++) m=m*10+num[j];
				if(m>n&&m<=b&&!vis[m]){
					vis[m]=1;
					ans++;
				}
			}
			for(int i=1;i<len;i++){
				int m=0;
				for(int j=i;j<len;j++) m=m*10+num[j];
				for(int j=0;j<i;j++) m=m*10+num[j];
				vis[m]=0;
			}
		}
		cout<<"Case #"<<kkk01<<": "<<ans<<endl;
	}
	return 0;
}
```

## 后记

新知识：会的都会，不会的可以看一下 ```memset(数组名称,0,sizeof(数组名称));```，使用这个方法，我们可以使用简捷的代码将数组归零，以上代码我也用到 ```memset```，大家可以去借鉴一下哦。

下次一定要看清楚数据范围再写，出错了就写不了题解了。

题解制作不容易如果决的我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

---

## 作者：WsW_ (赞：2)

### 思路
发现如果已知 $n$，那么仅有约 $\log_{10}n$ 个可能可行的 $m$。对于一组已知的 $(n,m)$，可以在 $O(1)$ 的时间内判断是否可行。  
所以可以在 $A\sim B$ 的范围内枚举 $n$，对于每个 $n$ 枚举可行的 $m$，并判断枚举出来的这一组 $(n,m)$ 是否可行。  
需要注意，可能会枚举出来的相同的 $m$。例如 $n=1212$ 把末尾的 $2$ 或 $212$ 移到最前面所得出的 $m$ 均为 $2121$。所以我们需要对 $m$ 判重，由于 $m$ 很小，各种方法都可以。  

我使用 STL 容器 `set` 进行判重，时间复杂度为 $O(B\log B\log\log B)$。  

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

set<int>s;
void work(){
	int cnt=0,a,b;cin>>a>>b;
	for(int n=a;n<=b;n++){
		s.clear();
		int l=0,p=1;
		for(int i=n/10;i>0;i/=10,l++,p*=10);
		for(int m=n,j=1;j<=l;j++){
			m=m%10*p+m/10;
			if(n<m&&m<=b)s.insert(m);
		}
		cnt+=s.size();
	}
	printf("%d\n",cnt);
}
int main(){
	int T; cin>>T;
	for(int i=1;i<=T;i++){
		printf("Case #%d: ",i);
		work();
	}
	return 0;
}
```

---

## 作者：matrixPower (赞：1)

[传送门](https://www.luogu.com.cn/problem/P13313)

简单模拟题。

注意到 $A,B\le2\times 10^6$，只能使用线性做法。

枚举 $x$ 在 $A,B$ 之间，再进行移位操作将移位后的值算出，判断其是否在 $A,B$ 之中，是否出现过就行了。

现在的难点就是如何位移。发现位移时出现首尾相接的情况，普通数组较难操作，所以可以开两倍空间进行——破环为链。这样位移操作就很方便了。

易错点：在做移位操作时，一个数可能变成两个相同的数。例如 $2121$，移动一位和三位都是 $1212$。记得判重。还有就是不能变成他自己。

时间复杂度 $O(nl^2)$，$n$ 为区间长度，$l$ 为数字位数。勉强可过。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lowbit(x) (x)&(-x)
using namespace std;

typedef double db;
typedef long long ll;
typedef __int128 III;
const db eps=1e-6;
const int inf=1e9;
void ll_cmax(ll &a,ll b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(int &a,int b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eps;}
bool number(char ch){return ch>='0' && ch<='9';}
bool lower(char ch){return ch>='a' && ch<='z';}
int sqlong(int n){int sq=sqrt(n)+1;return min(sq,n);}

const int MAXN=20;
int T,x,y,a[MAXN];

int check(int x,int l,int r)
{
	int cnt=0,tp=x;
	while(x>0)
	{
		a[++cnt]=x%10;
		x/=10;
	}
	for(int i=1;i<=cnt/2;i++) swap(a[i],a[cnt-i+1]);
	for(int i=cnt+1;i<=2*cnt;i++) a[i]=a[i-cnt];
	int ans=0;
	map<int,int>m;
	for(int i=1;i<=cnt;i++)
	{
		int sum=0;
		for(int j=i;j<=i+cnt-1;j++) sum=sum*10+a[j];
		if(sum>=l && sum<=r && sum!=tp && m.find(sum)==m.end()) m[sum]=114,++ans;
		//在做移位操作时，一个数可能变成两个相同的数。例如 2121，移动一位和三位都是 1212。记得判重。 
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	int cur=0;
	while(T--)
	{
		cin>>x>>y;
		++cur;
		cout<<"Case #"<<cur<<": ";
		int ans=0;
		for(int i=x;i<=y;i++) ans+=check(i,x,y);
		cout<<ans/2<<endl;
	}
	return 0;
}
//by Matrix_Power

```

---

## 作者：FHY_patrickpp (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/P13313)

## 分析

找多少不同的可循环对 $(n,m)$ 满足 $A⩽n<m⩽B$？

## 思路

对于每个 $n$，生成它所有可能的循环移位形式

验证移位后的数字：

- 检查是否在 $[A,B]$ 范围内

- 检查是否大于 $n$（避免重复计数）

- 检查是否有前导零


```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt(int a,int b) 
{
    unordered_set<string> ust;
    int ans=0,len,m;
    for(int n=a;n<=b;n++) 
	{
        string s=to_string(n);
        len=s.length();
        unordered_set<int> g;
        for(int i=1;i<len;i++) 
		{
            string cur=s.substr(i)+s.substr(0,i);
            if(cur[0]=='0') continue;
            if(stoi(cur)>n&&stoi(cur)>=a&&stoi(cur)<=b&&g.find(stoi(cur))==g.end()) 
			{
                g.insert(stoi(cur));
                ans++;
            }
        }
    }
    return ans;
}
int main() 
{
	int t;
    cin>>t;
    for(int i=1;i<=t;i++) 
	{
        int a,b;
        cin>>a>>b;
        cout<<"Case #"<<i<<": "<<cnt(a,b)<<"\n";
    }
    return 0;
}
```
这篇题解正常来说应该结束了，但是：

![](https://cdn.luogu.com.cn/upload/image_hosting/u2yohgia.png)


## 更新思路

使用字符串操作来生成循环移位效率低，所以我们用可以数值计算代替字符串操作。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt(int a,int b) 
{
	int ans=0;
	for(int n=a;n<=b;n++) 
	{
		int len=0,tmp=n,pow10=1;
		while(tmp) 
		{
			tmp/=10;
			++len;
		}
		for(int i=1;i<len;i++) pow10*=10;
		unordered_set<int> g;
		tmp=n;
		for(int i=1;i<len;i++) 
		{
			tmp=tmp/10+(tmp%10)*pow10;
			if(tmp>=a&&tmp<=b&&tmp>n&&g.find(tmp)==g.end()) 
			{
				g.insert(tmp);
				++ans;
			}
		}
	}
	return ans;
}
int main() 
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++) 
	{
		int a,b;
		cin>>a>>b;
		cout<<"Case #"<<i<<": "<<cnt(a,b)<<"\n";
	}
	return 0;
}
```

---

## 作者：shentianxing (赞：1)

显然，分别枚举所有数对会超时。但是，可以枚举 $n$ 然后模拟移位，最后统计符合条件的情况即可。

比如对于数 $1234$，移位一次得到 $4123$，满足条件。同样继续移位，$3412$ 和 $2341$ 都满足 $m > n$，如果它们没有越界，加入答案数。再次移位回到 $1234$ 结束循环。

但是对于数 $4312$，移位得到 $2431$，不满足 $m > n$，就不加入答案数。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int _10(int x){
	int t=1;
	while(t<=x){
		t*=10;
	}
	return t/10;
}

signed main(){
	int t;cin>>t;
	for(int b=1;b<=t;b++){
		int x,q;cin>>x>>q;int ans=0;
		for(int i=x;i<=q;i++){
			int y=i;
			do{
				int k=y%10;
				int u=y;
				y/=10;
				y+=_10(i)*k;
				if(y>i&&y<q){
					ans++;
				}
			}while(y!=i);
		}
		cout<<"Case #"<<b<<": "<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：cheny919 (赞：1)

### 题目分析
这个题目要求我们找可循环对的个数。我们很容易就可以想到枚举，分别枚举 $n$，$m$，并模拟移动数字的过程。但因为  $A\le B\le 2000000$，这样做一定会超时，所以我们需要想方设法进行优化。

这时我们注意到，我们只需要枚举出所有能通过移动数字得到 $m$ 的数就可以了。当然，你也可以枚举出 $n$ 移动数字之后能得到的所有数。

但是我们还需要判断枚举得到的数字符不符合 $A\le n <m \le B$ ，如果不符合就不增加可循环对的个数。

如果你的代码完成了以上的步骤，你就会发现你的代码甚至连样例都过不了。这是因为 $1212$ 这种数字可能会多次计数，我们还需要判断数字是否已经被计数了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long t,a,b,jishu=0,wei,wei2,cun1,cun2,cun3[10],cql[9999],wtr=0;
	cin>>t;
	for(int tt=1;tt<=t;tt++){
		jishu=0;//计数清零 
		cin>>a>>b;
		if(a<10){wei=1;wei2=1;}
		else if(a<100){wei=2;wei2=10;}
		else if(a<1000){wei=3;wei2=100;}
		else if(a<10000){wei=4;wei2=1000;}
		else if(a<100000){wei=5;wei2=10000;}
		else if(a<1000000){wei=6;wei2=100000;}
		else if(a<10000000){wei=7;wei2=1000000;}//以上用于判断数字位数。 
		for(int i=a+1;i<=b;i++){
			cun1=i;wtr=0;
			for(int k=1;k<wei;k++){
				cun2=cun1/wei2;
				cun2=cun2*wei2;
				cun1=cun1-cun2;
				cun1=cun1*10;
				cun2=cun2/wei2;
				cun1=cun1+cun2;
				cql[k]=cun1;//进行数字交换 
				for(int h=1;h<k;h++)
					if(cun1==cql[h])
						wtr=1;//判断是否已经计数 
				if(cun1>=a&&cun1<i&&wtr==0)
					jishu++;
			}
		}
		cout<<"Case #"<<tt<<":"<<" "<<jishu<<endl;
	}
}
```

---

