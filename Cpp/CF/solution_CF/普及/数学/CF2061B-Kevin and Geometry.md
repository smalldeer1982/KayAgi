# Kevin and Geometry

## 题目描述

凯文有 $ n $ 根长度分别为 $ a_1,a_2,\ldots,a_n $ 的木棍。

凯文想从这些木棍中选出 4 根来组成一个面积为正的等腰梯形  。请注意，矩形和正方形也被视为等腰梯形。请帮助凯文找到一个解决方案。如果不存在解决方案，请输出 -1 。

等腰梯形是一种凸四边形，有一条对称轴将一对对边平分。在任何等腰梯形中，两对边（底边）平行，另外两边（腰）长度相等。

## 说明/提示

在第一个测试用例中，您可以构建一个等腰梯形，其底边长度分别为 5 和 10，且两腰长度均为 5 。

在第二个测试用例中，您可以形成一个两底边长均为 5 且两腰长均为 10 的等腰梯形。这里矩形被视为等腰梯形。

在第三个测试用例中，没有长度相同的木棍。无法构成等腰梯形。

在第四个测试用例中，无法形成面积为正的等腰梯形。

## 样例 #1

### 输入

```
7
4
5 5 5 10
4
10 5 10 5
4
1 2 3 4
4
1 1 1 3
6
4 2 1 5 7 1
6
10 200 30 300 30 100
4
100000000 100000000 1 2```

### 输出

```
5 5 5 10
5 5 10 10
-1
-1
1 1 4 5
-1
100000000 100000000 1 2```

# 题解

## 作者：liuzhengtao (赞：2)

## 题目大意
给你 $t$ 组数据，每组数据中有 $n$ 根木棍，并告诉你每根木棍的长度，请你在其中选出四个木棍，使其可以构成一个**等腰梯形**。

这里标注一下，本来等腰梯形的定义是不包括正方形和矩形，但这道题却说这样也算上，所以感谢评论区一位大佬指出本蒟错误。
## 分析
本题考察的算法是贪心。
### 理论基础
两点之间线段最短。所以这个梯形的每一边的长度一定小于另外三个边边长之和。
### 贪心思路
1. 如果要构成等腰梯形，那么要让腰尽可能地长。即需找到最长的两个相等的木棍。
2. 先感性理解一下：剩余的两根木棍尽可能地长度差距小。即上下底的长度差尽量小。易证得这样最优。

原因：如果两者差值较大，那么两腰长与短边长的和减去长边的长得到的差值会较小，并且当其小于 $0$ 时，即为不成立（两点间线段最短）。

---

## 作者：Drifty (赞：2)

### Solution

忘记特判被叉掉了，破防了写一篇。

首先我们令四条边长为 $a,b,c,d$，设 $a \le b \le c \le d$，我们需要找到满足 $a + b + c > d$ 的四条边。

- 若 $c = d$，那么 $a + b + c > c$ 恒成立。
- 反之不妨设 $a \le b = b \le c$，那么我们要求 $a + 2b > c$，等价于 $2b > c - a$，因此最小化上下底差最大化腰长即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int T, n;
void solve() {
    cin >> n;
    vector <int> a(n);
    for (auto &i : a) cin >> i;
    sort (a.begin(), a.end());
    int f = -1;
    for (int i = n - 1; i; i --) if (a[i] == a[i - 1]) f = i;
    if (f == -1) return cout << -1 << '\n', void();
    if (f > 1 && f + 1 < n) if (a[f - 1] + a[f - 2] + a[f] > a[f + 1]) 
        return cout << a[f - 2] << ' ' << a[f - 1] << ' ' << a[f] << ' ' << a[f + 1] << '\n', void();
    for (int i = f + 2; i < n; i ++) 
        if (a[i - 1] + a[f] + a[f - 1] > a[i]) 
            return cout << a[i - 1] << ' ' << a[f] << ' ' << a[f - 1] << ' ' << a[i] << '\n', void();
    for (int i = 1; i < f - 1; i ++) 
        if (a[i - 1] + a[f] + a[f - 1] > a[i]) 
            return cout << a[i - 1] << ' ' << a[f] << ' ' << a[f - 1] << ' ' << a[i] << '\n', void();
    return cout << -1 << '\n', void();
}
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    for (cin >> T; T --; ) solve();
    return 0;
}
```

---

## 作者：c_legg (赞：2)

## 题意

给定 $n$ 个正整数 $a_i,i\in\mathbb{Z}\cap[0,n-1]$，其中 $a_i$ 表示第 $i$ 根木棒的长度为 $a_i$，求能否用其中 $4$ 根木棒拼成一个等腰梯形，如果能输出这 $4$ 根木棒的长度，如果不能，输出 $-1$。

## 思路

根据等腰梯形的定义，设腰长 $z$，底边和顶边长 $x,y$，$x\le y$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/l9lncgp1.png)

可以发现 $2z+x\gt y\ge x$，所以我们要让 $z$ 尽可能大，因为如果 $z$ 取小了，就可能会有解遗漏。

在确定了 $z$ 后，就把它们从 $a$ 中删除，接着对于每个 $a_i$，令 $x=a_i$，用二分找到第一个 $a_j$ 使 $2x+x\le a_j,j\gt i+1$，如果 $j$ 存在且 $j>0$ 的话，就让 $y=a_{j-1}$。

## 代码

非常简单 ~~我不会告诉你我在赛时都没做出这道题~~

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int t, n;

int a[200000+5];

int x, y, z;

void slove() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>a[i];
    sort(a, a+n);

    int x, y, z=0;

    for(int i=n-1; i>0; i--) {
        if(a[i]==a[i-1]) {
            z=a[i];
            a[i]=a[i-1]=1e9;
            sort(a, a+n);
            n-=2;
            break;
        }
    }

    if(z==0) {
        cout<<-1<<endl;
        return ;
    }

    for(int i=0; i<n; i++) {
        x=a[i];
        y=lower_bound(a+i+1, a+n, 2*z+x)-a;
        if(y==n && i==n-1) continue;
        y--;
        if(y==i) continue;
        cout<<x<<" "<<a[y]<<" "<<z<<" "<<z<<endl;
        return ;
    }

    cout<<-1<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin>>t;
                        
    while(t--) slove();
    return 0;
}
```

---

## 作者：_Mortis_ (赞：1)

### [CF2061B Kevin and Geometry](https://www.luogu.com.cn/problem/CF2061B)

## 题意

$ t $ 组数据，每组数据给定 $ n $ 根木棍的长度，求是否能用其中 $ 4 $ 根木棍组成**等腰梯形**，能则输出 $ 4 $ 根木棍的长度，否则输出 $ -1 $。

## 思路

设上底长 $ a $，腰长 $ b $，下底长 $ c $。

![](https://cdn.luogu.com.cn/upload/image_hosting/3usi68l9.png)

易知  $ a + 2b > c $ (两点之间线段最短)。

移项得 $ c - a < 2b $。

要使不等式成立，我们需要让不等式左边尽量小，右边尽量大。

所以先在长度相等的木棍中选**长度最大**的作为腰，再选剩下的木棍中**长度之差最小**的两根作为上底和下底，判断是否能组成等腰梯形即可。

### 坑点

题目中提到矩形也视为等腰梯形（"A rectangle is considered an isosceles trapezoid here."），但还要注意特判**正方形**。

---

## 作者：yvbf (赞：1)

![](bilibili:BV1MuwverEdQ?t=220)

---

## 作者：Pyrf_uqcat (赞：1)

只需分类讨论即可。

当有两对边相等时，即可将它们组成矩形，题意中说明了矩形也是等腰梯形。注意判断正方形。

当只有一对边相等时，无疑这一对边是腰。因为梯形需要三边之和大于第四边，所以只要再找两条长度差值最小的边来当上边和下边。进行判断，对则输出，错则无解。

当没有边相等，无法达成题目中的等腰，无解。

赛时已过代码：


```cpp
#include <bits/stdc++.h>
#define int long long

#define N 200005

using namespace std;

int n;

signed main()
{
	int t;cin>>t;
	while(t--)
	{
		map<int,int> mp;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int x;cin>>x;
			mp[x]++;
		}
		int cnt=0,mx=0,p=0,mi=INT_MAX;
		for(auto i:mp)
		{
			if(i.second>=2)
			{
				cnt++;
				if(mx!=0&&p==0) p=i.first;
				else mx=i.first;
			}
			if(i.second>=4)
			{
				cnt++;
				p=i.first,mx=i.first;
				break;
			}
		}
		if(cnt>=2)
		{
			cout<<min(mx,p)<<' '<<min(mx,p)<<' '<<max(mx,p)<<' '<<max(mx,p)<<endl;
		}
		else if(mx==0) cout<<-1<<endl;
		else
		{
			int z=-1,j=0,k=0;
			for(auto i:mp)
			{
				if(i.second!=2)
				{
					if(z!=-1&&i.first-z<mi)
					{
						j=z,k=i.first;
						mi=i.first-z;
					}
					z=i.first;
				}
			}
			if(j+mx*2<=k||j+k==0) cout<<-1<<endl;
			else
			{
				cout<<mx<<' '<<mx<<' '<<j<<' '<<k<<endl;
			}
		}
	}
    return 0;
}
```
`

---

## 作者：zhangxiao666 (赞：0)

考虑先找一下腰，直接找出现次数大于 $1$ 的数中最大的即可（为什么是最大的下面解释）。

然后要想构成等腰梯形，设上底为 $a$，下底为 $b$，腰为 $x$，则 $a+2x>b$，移项得到 $b-a<2x$，将数组排序在相邻的数中找即可（数组有序，相邻的差比不相邻的更小），而选择最大的腰才能使条件更宽松，避免误判。

[code](https://codeforces.com/contest/2061/submission/302228793)

---

## 作者：programmer330 (赞：0)

# 题解：CF2061B Kevin and Geometry

### 题意简述

本题有 $t$ 组数据，对于每组数据：有 $n$ 根木棍，长度依次为 $a_1,a_2,\cdots,a_n$。问其中能否选出 $4$ 根木棍，使得它们可以组成等腰梯形。

### 思路分析

这题不难，**贪心**思维含量不高，但是比较坑。

假设如果可以构造时最终木棍的长度依次为 $a,b,c,d$ 且 $a\le b\le c\le d$，那么根据数学知识可以知道可以搭建的充分条件是 $a+b+c > d$。

因为要构成等腰梯形，所以首先可以从给出的木棍中找出长度相等的木棍，并优先选择长的作为等腰边。这个时候假如等腰边中包含最长的木棍，那么就可以构造了，从剩下的木棍中任选两根即可；否则选择比等腰边长的最短木棍和比等腰边短的最长木棍。此时进行判定：$a+b+c$ 是否大于 $d$ 就可以了。

但是还没有完（一开始因为没考虑周全没切掉），注意**特判**是否会构成矩形或菱形，并将这种情况排除。

---

## 作者：_anll_ (赞：0)

## 思路
对于一个凸四边形，设其四条边分别为 $a,b,c,d$，钦定 $a\le b\le c\le d$，那么 $a+b+c>d$。对于 $d$ 而言会存在两种情况：

- 若 $d$ 为等腰边，那么 $c=d$，因此 $a+b+c> d$ 恒成立，可以随便处理。
- 若 $d$ 不为等腰边，那么我们就得让 $d$ 尽量小，$a,b,c$ 尽量大。

搞懂上面的限制后自然就得出了下面的构造逻辑：我们让等腰边尽量大，因为等腰边没有被任何约束限制。选好等腰边后，我们需要让上底和下底的差尽量小，差越小成功的可能性就越大。这里可以用排序，把未选中的边依次选择相邻边判断一下能否构成四边形，可以就直接输出，如果到最后都不行就报告无解即可。

## 代码
赛时代码比较丑提前致歉。
```cpp
#include<map>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=3e5+5;
int t,n,m,num[N];
map<int,int> mo;
void solve(){
	cin>>n;bool st=0;int a,b,c;mo.clear();
	for(int i=1;i<=n;i++) cin>>num[i];
	sort(num+1,num+1+n);
	for(int i=n;i>=1&&!st;i--){
		mo[num[i]]++;
		if(mo[num[i]]>1) st=1,a=i;
	}
	if(!st||n<4) return void(cout<<"-1\n");
	int las=-10000000000;
	for(int i=1;i<=n;i++){
		if(i==a||i==a+1) continue;
		if(num[a]*2+las>num[i]){
			cout<<num[a]<<" "<<num[a]<<" "<<las<<" "<<num[i]<<endl;
			return;
		}
		las=num[i];
	}
	cout<<"-1\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：postpone (赞：0)

看着比较和蔼，但做起来比较搞，而且容易漏想，我看很多人这题都 FST 了。

要达到题目要求，首先肯定需要一对腰，也就是相等的边。

其次，四条边要能组成一个四边形：上底和两条腰的长度之和要大于下底。

那么要怎么合理地选择呢？腰肯定越长越好；而上下底，差得越小越好。选完腰之后，找大小相邻的元素，判断是否合法即可。

实现层面，可以选用 $\texttt{std::map}$，但直接对数组排序更加好写。

```cpp
void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ranges::sort(a, greater());

    int u{}, v{}, w{};

    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            w = a[i];
            a.erase(find(a.begin(), a.end(), w));
            a.erase(find(a.begin(), a.end(), w));
            break;
        }
    }
    for (int i = 1; i < a.size(); i++) {
        if (a[i] + 2 * w > a[i - 1]) {
            u = a[i];
            v = a[i - 1];
            break;
        }
    }
    if (u and v and w) {
        cout << u << " " << v << " " << w << " " << w << "\n";
    } else {
        cout << -1 << "\n";
    }
}
```

---

