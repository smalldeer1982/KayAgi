# Glory Addicts

## 题目描述

The hero is addicted to glory, and is fighting against a monster.

The hero has $ n $ skills. The $ i $ -th skill is of type $ a_i $ (either fire or frost) and has initial damage $ b_i $ .

The hero can perform all of the $ n $ skills in any order (with each skill performed exactly once). When performing each skill, the hero can play a magic as follows:

- If the current skill immediately follows another skill of a different type, then its damage is doubled.

 In other words, 1. If a skill of type fire and with initial damage $ c $ is performed immediately after a skill of type fire, then it will deal $ c $ damage;
2. If a skill of type fire and with initial damage $ c $ is performed immediately after a skill of type frost, then it will deal $ 2c $ damage;
3. If a skill of type frost and with initial damage $ c $ is performed immediately after a skill of type fire, then it will deal $ 2c $ damage;
4. If a skill of type frost and with initial damage $ c $ is performed immediately after a skill of type frost , then it will deal $ c $ damage.

Your task is to find the maximum damage the hero can deal.

## 说明/提示

In the first test case, we can order the skills by $ [3, 1, 4, 2] $ , and the total damage is $ 100 + 2 \times 1 + 2 \times 1000 + 10 = 2112 $ .

In the second test case, we can order the skills by $ [1, 4, 2, 5, 3, 6] $ , and the total damage is $ 3 + 2 \times 6 + 2 \times 4 + 2 \times 7 + 2 \times 5 + 2 \times 8 = 63 $ .

In the third test case, we can order the skills by $ [1, 2, 3] $ , and the total damage is $ 1000000000 + 1000000000 + 1000000000 = 3000000000 $ .

In the fourth test case, there is only one skill with initial damage $ 1 $ , so the total damage is $ 1 $ .

## 样例 #1

### 输入

```
4
4
0 1 1 1
1 10 100 1000
6
0 0 0 1 1 1
3 4 5 6 7 8
3
1 1 1
1000000000 1000000000 1000000000
1
1
1```

### 输出

```
2112
63
3000000000
1```

# 题解

## 作者：yitian_ (赞：5)

## 题目分析

题目给出 $n$ 个技能的属性以及伤害，如果连续释放的两个技能属性不同，则后一个释放的技能伤害翻倍，否则不变。

要求设计出一种技能释放顺序，使得造成的总伤害最高。

## 思路

使用两个数组分别存储两种技能的伤害值，并按照从小到大的顺序排序。然后求出火技能的数量 $cnta$ 和冰技能的数量 $cntb$，以及它们的差 $dv$。

基于贪心的思路，如果 $cnta>cntb$，就先释放伤害较小的 $dv$ 个火技能。然后将剩下的 $cntb$ 个冰技能和 $cntb$ 个火技能交替释放，以造成双倍伤害。

如果 $cntb>cnta$，那就反过来，先释放伤害较小的 $dv$ 个冰技能，再交替释放剩下的 $cntb$ 个火技能和 $cntb$ 个冰技能。

如果 $cnta=cntb$，直接交替释放即可。但是需要注意的是，第一个释放的技能是无法打出双倍伤害的，需要处理一下。

## C++ 代码实现 

```c
#include<bits/stdc++.h>
using namespace std;

int a[200010],b[200010]; // 数组 a 存储火技能的初始伤害，数组b存储冰技能的初始伤害
int atr[200010]; // 数组 atr 存储每个技能的属性 

int main()
{
    int t;
    cin >> t;
    while(t--)
	{
        int n;
	    cin >> n;
	    long long ans=0; 
	    int cnta=0,cntb=0; // cnta 记录火技能的数量，cntb 记录冰技能的数量
	    // 读入技能属性 
	    for(int i=1;i<=n;i++) 
	    {
	    	cin >> atr[i];
		}
		// 读入技能初始伤害，并根据属性存入对应的数组中
	    for(int i=1;i<=n;i++)
		{
			int c;
			cin >> c;
	        if(atr[i]==0)
			{
				cnta++;
	            a[cnta]=c;
	        }
	        if(atr[i]==1)
			{
				cntb++;
	            b[cntb]=c;
	        }
	    }
	    // 对两个数组进行排序
	    sort(a+1,a+cnta+1);
	    sort(b+1,b+cntb+1);
	    if(cnta>cntb)
		{
	        int dv=cnta-cntb;
	        for(int i=1;i<=dv;i++) ans+=a[i];
	        for(int i=dv+1;i<=cnta;i++) ans+=a[i]*2;
	        for(int i=1;i<=cntb;i++) ans+=b[i]*2;
	    }
	    else if(cntb>cnta)
		{
	        int dv=cntb-cnta;
	        for(int i=1;i<=dv;i++) ans+=b[i];
	        for(int i=dv+1;i<=cntb;i++) ans+=b[i]*2;
	        for(int i=1;i<=cnta;i++) ans+=a[i]*2;
	    }
	    else 
		{
	        for(int i=1;i<=cnta;i++) ans+=a[i]*2;
	        for(int i=1;i<=cntb;i++) ans+=b[i]*2;
	        // 第一个释放的技能无法打出双倍伤害 
	        if(a[1]<=b[1]) ans-=a[1];
	        else ans-=b[1];
	    }
	    cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：__owowow__ (赞：2)

## CF1738A Glory Addicts题解
### 题目大意
题目给出 $n$ 个技能的属性以及伤害，属性有两种。如果连续释放的两个技能属性不同，则第二个释放的技能伤害翻倍，否则不变。要求设计出一种技能释放顺序，使得造成的总伤害最高。

**有 $t$ 组数据！** ~~关键是翻译也没说啊~~

### 思路
考虑贪心算法。设第一种属性有 $n_a$ 个技能，第二种属性有 $n_b$ 个技能。则有三种情况：

- 当 $n_a < n_b$ 时，先释放 $n_b-n_a$ 个二级技能，之后交替释放 $n_a$ 个技能。
- 当 $n_a > n_b$ 时，先释放 $n_a-n_b$ 个二级技能，之后交替释放 $n_b$ 个技能。
- 当 $n_a = n_b$ 时，直接交替释放 $n_a$ 个技能。注意：**第一个技能无法双倍伤害！**

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MA 200005
#define int long long
int n,a[MA],b[MA],na,nb,t,ans,shu[MA],dam,pre;
signed main(){
    cin>>t;
    while(t--){//多测
        cin>>n;
        ans=0,na=0,nb=0;
        for(int i=1;i<=n;i++) cin>>shu[i];
        for(int i=1;i<=n;i++){
            cin>>dam;
            if(shu[i]==0) a[++na]=dam;
            else b[++nb]=dam;
        }
        sort(a+1,a+na+1);
        sort(b+1,b+nb+1);
        if(na>nb){
            pre=na-nb;
            for(int i=1;i<=pre;i++) ans+=a[i];
            for(int i=1;i<=nb;i++) ans=ans+a[i+pre]*2+b[i]*2;
        }
        else if(nb>na){
            pre=nb-na;
            for(int i=1;i<=pre;i++) ans+=b[i];
            for(int i=1;i<=na;i++) ans=ans+b[i+pre]*2+a[i]*2;
        }
        else{
            for(int i=1;i<=na;i++) ans+=2*(a[i]+b[i]);
            ans-=min(a[1],b[1]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：zjzx_wcj (赞：1)

# 题解：CF1738A Glory Addicts

[题目传送门](https://www.luogu.com.cn/problem/CF1738A)

## 思路

一道很简单的贪心题。。。~~一遍过~~

首先，我们读入，按数据分类（这个没问题吧）。

然后，我们排序。

接着（最重要的部分来了），如果火技能的个数不等于冰技能，把小的技能加入答案（是个数多的那方），否则，全部加起来 $\times2$，再减去火技能和冰技能中最小的即可。

提示：可以使用动态数组（[vector](https://blog.csdn.net/wkq0825/article/details/82255984)）存储。`a.size ()` 可以用来表示数组 $a$ 的元素个数，不需要额外的变量。

## 代码展示：

为了防止 ctj，代码只给出核心，其余自己完成（快读够你受的了）。

```cpp
inline int cl (int x,int y) {return (x+y)*2;}
inline void work (void)
{
	int n=read ();
	vector<int> a (n+1),b (1),c (1);
	reg (i,1,n) a[i]=read ();
	reg (i,1,n) {int x=read ();if (a[i]) c.push_back (x);else b.push_back (x);}
	sort (b.begin ()+1,b.end ());
	sort (c.begin ()+1,c.end ());
//	reg (i,1,b.size ()-1) write (b[i]),putchar (' ');
//	putchar ('\n');
//	reg (i,1,c.size ()-1) write (c[i]),putchar (' ');
//	putchar ('\n');
	int maxn=0;
	if (b.size ()>c.size ()) 
	{
		int za=b.size ()-c.size ();
		reg (i,1,za) maxn+=b[i];
		reg (i,1,c.size ()-1) maxn+=cl (c[i],b[i+za]);
	}elif (b.size ()<c.size ())
		{
			int za=c.size ()-b.size ();
			reg (i,1,za) maxn+=c[i];
			reg (i,1,b.size ()-1) maxn+=cl (b[i],c[i+za]);
		}else
		{
			reg (i,1,b.size ()-1) maxn+=cl (b[i],c[i]);
			if (b[1]<c[1]) maxn-=b[1];
				else maxn-=c[1];			
		}
	writeln (maxn);
	return ;
}
```

---

## 作者：ScottSuperb (赞：1)

## 解法分析
简单贪心题。因为一个技能在不同种技能后使用才可以产生双倍伤害，所以我们需要尽可能将初始伤害大的技能间隔着放。那么记录不同技能类型总数为 $s0$ 和 $s1$，则可分为以下三种情况：

1. $s0=s1$，这时可将左右技能间隔放，初始伤害最小的放第一个以舍掉；
1. $s0<s1$，这时为了尽可能产生更多的双倍伤害，应将冰技能多出来的初始伤害较少的舍掉；
1. $s0>s1$，同上，应将火技能多出来的初始伤害较少的舍掉。

这里“舍掉”即指不让它产生双倍伤害。在代码实现中可先排序，再将舍掉的单独计入答案并清零它的初始伤害，最后再扫一遍所有技能将双倍伤害计入答案即可。**别忘了使用 `long long` 记录答案！**
## 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
 
struct skill {
  int a, b;
  skill(int a0 = 0, int b0 = 0) { a = a0, b = b0; }
  bool operator<(skill sk) {
    if (a == sk.a) return b < sk.b;
    return a < sk.a;
  }
} s[100005];
 
int main() {
  int t = read(), n, s0, s1;
  ll ans;
  while (t--) {
    n = read();
    ans = s0 = s1 = 0;
    for (int i = 0; i < n; ++i) {
      s[i].a = read();
      if (s[i].a)
        ++s1;
      else
        ++s0;
    }
    for (int i = 0; i < n; ++i) s[i].b = read();
    sort(s, s + n);
    if (s0 == s1) {
      if (s[0].b < s[s0].b)
        ans += s[0].b, s[0].b = 0;
      else
        ans += s[s0].b, s[s0].b = 0;
    } else if (s0 < s1)
        for (int i = s0; i < s1; ++i) ans += s[i].b, s[i].b = 0;
    else
        for (int i = 0, ii = s0 - s1; i < ii; ++i) ans += s[i].b, s[i].b = 0;
    for (int i = 0; i < n; ++i) ans += s[i].b << 1;
    write(ans);
  }
  return 0;
}
```

---

## 作者：Allanljx (赞：1)

## 思路
贪心，显然 $a_i$ 要 $0/1$ 间隔着放，所以用两个数组分别记录 $a_i=0$ 和 $a_i=1$，然后按 $b_i$ 从大到小排序，先放数量少的，然后放数量多的，多余的选一个放在位置 $1$。注意特判一下当 $0$ 和 $1$ 的数量一样的时候要挑一个 $b_i$ 最小的放在位置 $1$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
struct node
{
	int a,b;
}c[100005],d[100005],e[100005];
int t1,t2,ans;
bool cmp(node aa,node bb)
{
	return aa.b>bb.b;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		ans=t1=t2=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>c[i].a;
		for(int i=1;i<=n;i++)
		{
			cin>>c[i].b;
			if(c[i].a) d[++t1]=c[i];
			else e[++t2]=c[i];
		}
		sort(d+1,d+t1+1,cmp);
		sort(e+1,e+t2+1,cmp);
		for(int i=1;i<=max(t1,t2);i++)
		{
			if(i<=t1) ans+=d[i].b;
			if(i<=t2) ans+=e[i].b;
			if(i<=min(t1,t2)) ans+=d[i].b+e[i].b;//可以间隔着放
		}
		if(t1==t2) ans-=min(d[t1].b,e[t2].b);//挑一个放位置1
		cout<<ans<<endl;
	}
}
```

---

## 作者：Laisira (赞：1)

## 题解：CF1738A Glory Addicts
### 题面
给出两个 $n$ 个元素的序列 $a$ 和 $b$，每个 $i$ 的贡献为：

$\begin{cases}
  b_i\  ,i=1\ 或\ a_i=a_{i-1} \\
  2\times b_i\ ,\  a_i \ne a_i-1
\end{cases}$

改变数列顺序，最大化贡献。

### 思路
我们发现因为 $b_i$ 非负，最大化贡献就是让更大的数到第二档。

分类讨论：

- 当任意 $a_i$ 出现数量小于其他时，显然可以所有数错位排序，设最小 $b_i$ 为 $minv$，贡献是 $\sum_{i = 1}^{n}{b_i} \ - minv$。

- 否则就一定会有一段 $a_i$ 连续，用优先队列维护一下最小值，去掉前面一堆最小的必须重复的 $m$ 个数（$m$ 等于 $a_i$ 的数量减去不是 $a_i$ 的数量），后面的可以以一个 $a_i$ 一个非 $a_i$ 排列，就一定能全部到第二档。

### 代码
```cpp
#include <iostream>
#include <queue>
#include <map>
#define int long long 
using namespace std;
map<int,int> mp;
int a[500005];
priority_queue<int> q[500005]; 
signed main()
{
	int t;
	cin>>t;
	while(t--) {
		int n,tot=0,minv=INT_MAX,ans=0,g=0;
		cin>>n;
		mp.clear();
		for(int i=1;i<=n;i++) {
			while(!q[i].empty())
				q[i].pop();
			cin>>a[i];
			if(!mp.count(a[i]))
				mp[a[i]]=++tot;
		}
		for(int i=1,b;i<=n;i++) {
			cin>>b; minv=min(minv,b);
			ans+=b<<1;
			q[mp[a[i]]].push(-b);
			if(q[g].size()<q[mp[a[i]]].size())
				g=mp[a[i]];
		}
		int op=q[g].size(),opt=n-op;
		if(op>opt)
			while(op>opt)
				ans+=q[g].top(),
				q[g].pop(),
				op--;
		else ans-=minv;
		cout<<ans<<"\n";
	}
	return 0;
 } 
```

---

## 作者：Land_ER (赞：1)

## 题意简述
- 你有 $n$ 种技能，第 $i$ 种技能有属性 $a_i$ 和伤害 $b_i$。
- 若当次释放的技能属性与上一次不同，则该次技能伤害翻倍。
- 求最大总伤害。

## 解题思路
我们将技能编号按照对应的属性分成两组，记元素个数多的一组为 $p_1, p_2, \dots, p_x$，个数少的一组为 $q_1, q_2, \dots, q_y$，后分两种情况：

1. 若 $x = y$，则只有一个技能伤害无法翻倍。容易得知，当伤害最小的技能伤害未翻倍时最优。
2. 若 $x \neq y$，则 $q_1, q_2, \dots, q_y$ 全部可以伤害翻倍，而 $p_1, p_2, \dots, p_x$ 中只有 $y$ 项的伤害可以翻倍， 剩余的 $x - y$ 项不能翻倍。同样，我们取 $p_1, p_2, \dots, p_x$ 中伤害最小的 $x - y$ 项不翻倍时最优。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> fire, frost;
int a[100005], b;

void solve(void) {
    int n;
    long long int ans = 0;
    cin >> n;
    fire.clear();
    frost.clear();
    for(int i = 0; i < n; ++ i)
        cin >> a[i];
    for(int i = 0; i < n; ++ i) {
        cin >> b;
        ans += 2ll * b;
        if(!a[i])
            fire.push_back(b);
        else
            frost.push_back(b);
    }
        
    if(fire.size() < frost.size())
        swap(fire, frost);
    sort(fire.begin(), fire.end());
    sort(frost.begin(), frost.end());

    if(fire.size() == frost.size())
        ans -= min(fire[0], frost[0]);
    else
        for(int i = 0, s = fire.size() - frost.size(); i < s; ++ i)
            ans -= fire[i];
        
    printf("%lld\n", ans);

    return;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

输入两个序列 $a$ 与 $b$，若 $a_i=a_{i-1}$ 或者 $i=1$ 答案就加上 $b_i$，否则加上 $2\times b_i$。现在可以更改顺序，求最大答案。

## 解答

可以想到应该尽量让 $2\times b_i$ 的个数大，所以让 $a_i\ne a_{i-1}$ 的情况尽量多，所以要让序列中 $a$ 的值为一个 $0$ 一个 $1$ 这样排序。

那么就可以开两个数组，一个存 $a_i=1$ 时的 $b_i$，设为 $o$（one），一个存 $a_i=0$ 时的 $b_i$，设为 $z$（zero）。每次一起遍历这两个数组，遍历到一个 $i$ 时，就将两个数组的数一起加到答案数组中（方便错位排序）。即若当前有一个数组中的数还没用完，就将答案加上之；两个数组中都有数没用完时就加上两个数的和乘二。

所以容易得出 $o$ 与 $z$ 应该从大到小排序，使得乘二的次数尽量多。

而 $i=1$ 的情况，就弄个最小的数凑上去（因为乘不了二）。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t,n,a[100001],b,tt,tot,sum,z[100001],o[100001];
bool cmd(int x,int y)
{
	return x > y;
}

signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
		tt = tot = sum = 0;
		for(int i = 1;i <= n;i++)
		{
			scanf("%lld",&b);
			if(a[i]) o[++tot] = b;//a[i]等于一的情况
			else z[++tt] = b;
		}
		sort(o + 1,o + tot + 1,cmd);//大到小排序
		sort(z + 1,z + tt + 1,cmd);
		for(int i = 1;i <= max(tt,tot);i++)
		{
			if(i <= tt)//z[i]数组中有剩余的数
			{
				sum += z[i];
				if(i <= tot) sum += o[i] + z[i] + o[i];//两个都有数，可以乘二
			}
			else if(i <= tot) sum += o[i];//只有一个有数
		}
		if(tt == tot) sum -= min(o[tot],z[tt]);//第一个数重复加了（因为一定乘不了二）
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
英雄可以发动 $n$ 个技能，每个技能有一个伤害值和一个属性（冰或火（用 $1$ 和 $0$ 表示）），当当前技能的属性与上一个释放的技能属性不同时，当前这个技能伤害翻倍。

现在给你这 $n$ 个技能的属性 $a_i$ 和伤害值 $b_i$，问你以什么顺序释放这些技能可以使伤害最大化。

## 思路
考虑要让伤害最大化，因此尽量要把伤害值大的技能给翻倍。我们设属性为 $0$ 的技能有 $cnt_0$ 个，属性为 $1$ 的技能有 $cnt_1$ 个，我们只需比较 $cnt_0$ 与 $cnt_1$ 的大小关系。

若 $cnt_0=cnt_1$，则我们选取伤害值最小的那个作为开始，然后交替使用冰与火技能。

若 $cnt_0<cnt_1$，则我们可以把所有 $a_i=0$ 的技能都翻倍，把前 $cnt_0$ 大的 $a_i=1$ 的技能翻倍，其他 $a_i=1$ 的技能不能翻倍。

若 $cnt_0>cnt_1$，情况类似上面，这里不再赘述。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t=1,n,f[100005],a0[100005],a1[100005],cnt0,cnt1,tmp,ans;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    cnt0=cnt1=0;
    rep(i,1,n)cin>>f[i];
    rep(i,1,n){
      cin>>tmp;
      if(f[i]==0)a0[++cnt0]=tmp;
      else a1[++cnt1]=tmp;
    }
    ans=0;
    sort(a0+1,a0+cnt0+1);
    sort(a1+1,a1+cnt1+1);
    if(cnt0<=cnt1){
      rep(i,1,cnt0){
        ans+=2*a0[cnt0-i+1];
        ans+=2*a1[cnt1-i+1];
      }
      if(cnt0==cnt1)ans-=min(a1[1],a0[1]);
      rep(i,1,cnt1-cnt0){
        ans+=a1[i];
      }
    }
    else{
      rep(i,1,cnt1){
        ans+=2*a1[cnt1-i+1];
        ans+=2*a0[cnt0-i+1];
      }
      rep(i,1,cnt0-cnt1){
        ans+=a0[i];
      }
    }
    cout<<ans<<endl;
  }
  return 0;
}
```

---

## 作者：maxyzfj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1738A)

## 题解正文

#### 思路
由题意得，如果连着释放两个属性不同的技能，那么后释放的技能的伤害就是双倍的，因此我们可以考虑贪心：最大化相邻两个不同属性的技能的数量，在此前提下，令后一个技能的伤害尽可能大（贪心的证明放到后面）。

#### 实现方式
我们设属性为火的技能有 $x$ 个，属性为霜的技能有 $y$ 个。如果 $x< y$，则根据贪心思想，重新排列后前 $2x+1$ 个技能的属性应为霜和火的交错（第一个技能的属性为霜）。并且保证放在火技能的后面的霜技能尽可能大。答案也就是所有技能初始伤害之和再加上火技能初始伤害的和再加上伤害最大的 $x$ 个霜技能（此处可以排序）。$y>x$ 时同理。

而如果 $x=y$，显然的，答案就是所有技能初始伤害之和。再加上除伤害最小的技能外其他技能初始伤害之和。

#### 贪心证明
我们设属性为火的技能有 $x$ 个，属性为霜的技能有 $y$ 个。不妨设 $x\le y$。则至多有 $2x$ 个技能的伤害翻了倍。而如果调换顺序，则一定是将不同属性的调换（如果是相同属性的那么不会比已有答案更好），那么一定会使 $3$ 个霜属性的技能连在一起，使得至少一个霜属性技能无法获得双倍伤害，而原本被调换的火属性技能调换后，它后面如果是霜属性，那么一定不超过调换前任何一个霜属性技能的伤害，因此，调换后一定不会比原来好，因此贪心成立。

#### 时间复杂度
因为要排序，所以时间复杂度为 $O(n\log n)$。

#### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int x=0,f=1;
    char ch=getchar();
	while (ch<'0'||ch>'9'){
    	if (ch=='-') f=-1;ch=getchar();
    }
	while (ch>='0'&&ch<='9'){
    	x=x*10+ch-48;ch=getchar();
    }
	return x*f;
}
void write(int x){
    if(x<0){
		putchar('-'),x=-x;
	}
    if(x>9){
		write(x/10);
	}
    putchar(x%10 +'0');
}
const int inf=1000000007;
int t,n,a[100005],b[100005],c[100005];//a存属性，b存火属性技能的伤害，c存霜属性技能的伤害。
signed main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		int sum=0,x=0,y=0;sum://sum为所有技能的初始伤害之和；x为火属性技能的数量；y为霜属性技能的数量。 
		for(int i=1;i<=n;i++){
			if(a[i]==0){
				x++;
				b[x]=read();
				sum+=b[x];
			}
			else{
				y++;
				c[y]=read();
				sum+=c[y];
			}
		}
		int minn=min(x,y);
		if(x==y){//特判火属性技能和霜属性技能相等的情况。
			int k=inf+10;//k为最小伤害值。
			for(int i=1;i<=x;i++){
				k=min(k,b[i]);
			}
			for(int i=1;i<=y;i++){
				k=min(k,c[i]);
			}
			write(sum*2-k);putchar('\n');
		}
		else{
			int k=0;//k为因双倍伤害而增加的伤害。
			if(minn==x){
				for(int i=1;i<=x;i++){
					k+=b[i];
				}
				sort(c+1,c+y+1);
				for(int i=y;i>=y+1-minn;i--){
					k+=c[i];
				}
			}
			else{
				for(int i=1;i<=y;i++){
					k+=c[i];
				}
				sort(b+1,b+x+1);
				for(int i=x;i>=x+1-minn;i--){
					k+=b[i];
				}
			}
			write(sum+k);
			putchar('\n');
		}
	}
	return 0;
}
```

---

