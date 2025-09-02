# [NOISG 2021 Qualification] Competition

## 题目描述

你是一位老师，有 $n$ 个学生，每个学生都有物理成绩 $A_i$ 和生物成绩 $B_i$，你要从这些学生中选出 $a$ 个人参加物理竞赛，$b$ 个人参加生物竞赛。每个学生必须参加一种且只能参加一种竞赛。

定义你所在的学校的实力值为参加物理竞赛的人的物理成绩和参加生物竞赛的人的生物成绩的和。请你求出实力值最大是多少？

## 说明/提示

#### 样例 1 解释

第一、三个人参加生物竞赛，第二个人参加物理竞赛。

#### 数据范围

**本题采用捆绑测试。**

Subtask0 是样例。

Subtask1（29 pts）$n \leq 20$。

Subtask2（22 pts）保证所有 $B_i=0$。

Subtask3（49 pts）无特殊限制。

数据保证 $1 \leq n \leq 10^5$，$0 \leq a,b \leq n$，$a+b=n$，$0 \leq A_i,B_i \leq 10^4$。

## 样例 #1

### 输入

```
3 1 2
5 3 4
7 1 4```

### 输出

```
14```

## 样例 #2

### 输入

```
5 3 2
5 6 6 5 1
0 0 0 0 0```

### 输出

```
17```

# 题解

## 作者：liaoxingrui (赞：12)

## Content

给你一个 $n$、$n$ 个物理成绩 $A_i$ 和 $n$ 个生物成绩 $B_i$。从中取出 $a$ 个物理成绩和 $b$ 个生物成绩（不能取同一个位置上的），求总和最大。

$1 \le n \le 10^5$，$0 \le a,b \le n$，$0 \le A_i,B_i \le 10^4$，$a + b = n$。

## Solution

我们可以知道 $a + b = n$，也就是每个位置的成绩都要选一个。

我们可以通过贪心来做，如果 $A_i - B_i$ 越大，那么就选他的物理成绩，如果 $A_i - B_i$ 越小，那么就选他的生物成绩，因为都要选，就不用在考虑空的位置了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,x,y,z,cnt,ans;
struct node{
	int x,y,z;
}a[N];
inline bool cmp(node x,node y){
	return x.z<y.z;
}
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
		cin>>a[i].x;
	for(int i=1;i<=n;i++){
		cin>>a[i].y;
		a[i].z=a[i].x-a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=y;i++)
		ans+=a[i].y;
	for(int i=y+1;i<=n;i++)
		ans+=a[i].x;
	cout<<ans;
	return 0;
}
```

---

## 作者：_Star_Universe_ (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/P10771)
### 思路
这是一道简单的贪心题，我们可以定义一个结构体，在结构体中定义一个变量 $c$ 表示 $A_i-B_i$ 的值，即第 $i$ 个学生物理成绩 $A_i$ 与其生物成绩 $B_i$ 的差值，这个差值越大就说明该学生越适合参加物理竞赛，否则就说明该学生越适合参加生物竞赛，所以我们可以写一个结构体排序的函数，根据每组 $c$ 的大小进行降序排列，前 $a$ 名参加物理竞赛，后 $b$ 名参加生物竞赛，这样便可使总的实力值最大。

---

## 作者：FurippuWRY (赞：4)

定义 `pair` 数组 $t$，对于 $\forall i\in[1,n]$，$t_{i_{first}}=B_i - A_i,t_{i_{second}}=A_i$。

对 $t$ 进行排序（`pair` 自带的排序规则是按照 `first` 成员进行升序排序），这样可以使物理更强的学生排在前面（$t_{i_{first}}=B_i - A_i$，若 $t_{i_{first}}<0$，则 $B_i<A_i$，此学生的物理更强）。

定义变量 $ans=0$，然后分别从数组前后遍历 $a$ 次、$b$ 次，对于数组前部的遍历，$ans\leftarrow ans + t_{i_{second}}$（$t_{i_{second}}$ 等于学生的物理成绩）；对于数组后部的遍历，$ans\leftarrow ans + t_{i_{first}}+t_{i_{second}}$（因为 $t_{i_{first}}=B_i - A_i$，那么 $t_{i_{first}}+t_{i_{second}}=B_i - A_i + A_i = B_i$，为生物成绩）。

最后输出 $ans$ 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 9;

int n, a1, b1, a[N], b[N], ans = 0;
pair<int, int> t[N];

int main() {
	cin >> n >> a1 >> b1;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		t[i].first = b[i] - a[i];
		t[i].second = a[i];
	}
	sort(t + 1, t + n + 1);
	for (int i = 1; i <= a1; ++i) {
		ans += t[i].second;
	}
	for (int i = n, j = 1; j <= b1; --i, ++j) {
		ans += (t[i].first + t[i].second);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ggylz49 (赞：2)

看完题目后，我们可以马上想到：可以使用结构体来存储学生的生物和物理成绩，再使用排序算法来排序学生适合参加什么竞赛。

为了方便排序，可以构造一个 $C_i=A_i-B_i$。若 $C_i>0$，则这名学生的物理成绩大于生物成绩，适合参加物理竞赛；否则说明这名学生的物理成绩小于或等于生物竞赛，更适合参加生物竞赛。

所以对于按 $C_i$ **从大到小**排序后的数组，前 $a$ 个学生的 $C_i$ 是偏大的，相对适合参加物理竞赛；后 $b$ 个学生的 $C_i$ 是偏小的，相对适合参加生物竞赛。

对于排序后的数组，最终答案 $ans=A_1+A_2+\cdots+A_a+B_{a+1}+B_{a+2}+\cdots+B_b$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct student
{
    int A,B,C;//物理成绩、生物成绩和便于排序的Ci
}v[100010];
bool cmp(student x,student y)
{
    return x.C>y.C;
}
int main()
{
    int n,a,b,ans=0;//答案
    cin>>n>>a>>b;
    for (int i=0;i<n;i++)cin>>v[i].A;
    for (int i=0;i<n;i++)cin>>v[i].B;
    for (int i=0;i<n;i++)v[i].C=v[i].A-v[i].B;//初始化Ci
    sort(v,v+n,cmp);//依托cmp函数排序
    for (int i=0;i<a;i++)ans+=v[i].A;//前a人
    for (int i=a;i<n;i++)ans+=v[i].B;//后b人
    cout<<ans;//输出
    return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：1)

## 解题思路：
贪心题，将 $n$ 个学生按照 $A_i - B_i$ 的大小从大到小排序，那么显然前 $a$ 人该去参加物理竞赛，后 $b$ 人应当参加生物竞赛，计算输出即可。
## CODE:
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, a, b, ans;
struct sub
{
    int A, B;
}s[100001];
bool cmp(sub a, sub b)
{
    return (a.A - a.B) > (b.A - b.B);
}
int main()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cin >> s[i].A;
    for (int i = 1; i <= n; i++)
        cin >> s[i].B;
    sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= a; i++)
        ans += s[i].A;
    for (int i = n; i >= n - b + 1; i--)
        ans += s[i].B;
    cout << ans;
    return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：1)

我又把贪心和 dp 弄混了……

真心希望大家不要再踩坑。

## 进入正题

题目已经告诉我们了 $a+b=n$，所以意味着每个人要么只参加物理，要么只参加生物。

假如小 F 两门成绩分别为 114 和 514，那么小 F 肯定会去参加生物竞赛，换句话说，小 F 去参加物理竞赛的损失为 400，参加生物竞赛的损失为 -400。我们要让利润最大化既让损失最小化。

所以，以 $B_i-A_i$ 是第 $i$ 个人参加物理竞赛的损失，我们按 $B_i-A_i$ 为参数，让前 $a$ 人参加物理竞赛，后 $b$ 人参加生物竞赛即为最优策略。

附上超短 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b,c;
}t[100005];
signed main()
{
    int n,a,b,ans=0;cin>>n>>a>>b;
    for(int i=1;i<=n;i++)cin>>t[i].a;
    for(int i=1;i<=n;i++)cin>>t[i].b;
    sort(t+1,t+1+n,[](node x,node y){return x.b-x.a<y.b-y.a;});
    for(int i=1;i<=n;i++)
    ans+=(i<=a?t[i].a:t[i].b);
    cout<<ans;
	return 0;
}
```

---

## 作者：hard_learn (赞：1)

# 简要题意
题目要求计算出在给定学生列表中，通过选择一定数量的学生，使得他们的总体强度值最大化。每个学生有两个分数，一个是物理分数 $A_i$，一个是生物分数 $B_i$。选取的学生中，要求选取的前 $a$ 个学生使得他们的物理分数总和最大，并选取的后 $b$ 个学生使得他们的生物分数总和最大。
# 思路
$A_i - B_i$ 的值降序排序学生，这个值越大表示物理分数相对较高，生物分数相对较低。根据排序结果，分别取前 $a$ 个学生和后 $b$ 个学生。计算前 $a$ 个学生的物理分数总和和后 $b$ 个学生的生物分数总和，这两个总和之和即为目标值，即最大化的总体强度值。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,ans=0;
struct st{
	int df;
	int w,s;
};
bool cmp(st ww,st ss){
	if(ww.df!=ss.df){
		return ww.df>ss.df;
	}
	else{
		return ww.w>ss.w;
	}
}
int fx(int n,int a,int b,vector<int>& A,vector<int>& B){
	vector<st> students(n);
	for(int i=0;i<n;i++){
		students[i].df=A[i]-B[i];
		students[i].w=A[i];
		students[i].s=B[i];
	} 
	sort(students.begin(),students.end(),cmp);
	for(int i=0;i<a;i++){
		ans+=students[i].w;
	}
	for(int j=0;j<b;j++){
		ans+=students[n-j-1].s;
	}
	return ans;
}
signed main(){
	cin>>n>>a>>b;
	vector<int> A(n),B(n); 
	for(int i=0;i<n;i++){
		cin>>A[i];
	}
	for(int j=0;j<n;j++){
		cin>>B[j];
	}
	cout<<fx(n,a,b,A,B)<<endl;
}
```

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10771)

贪心秒了。

令 $C_i=A_i-B_i$。显然，相对于所有 $n$ 名学生，较大的 $C_i$ 表示该学生可能更适合物理竞赛，较小的 $C_i$ 表示该学生可能更适合生物竞赛。

于是我们根据 $C_i$ 大小排序即可。显然答案为前 $a$ 名学生的物理成绩 $A_i$ 总和加上后 $b$ 名学生的生物成绩 $B_i$ 总和的总和。

过程可以使用结构体排序实现。

```cpp
struct node
{
	int x,y,z;
}a[100010];
inline bool cmp(node x,node y)
{
	return x.z>y.z;
}
signed main()
{
	int n,p,q;
	rd(n,p,q);
	for(int i=1;i<=n;i++)
	{
		rd(a[i].x);
	}
	for(int i=1;i<=n;i++)
	{
		rd(a[i].y),a[i].z=a[i].x-a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;
	for(int i=1;i<=p;i++)
	{
		ans+=a[i].x;
	}
	for(int i=p+1;i<=n;i++)
	{
		ans+=a[i].y;
	}
	wtl(ans);
	return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 题意概述
从 $n$ 对 $\{A,B\}$ 中，选取 $a$ 对和 $b$ 对，使得选取的 $a$ 对的 $A$ 与 $b$ 对的 $B$ 的总和最大
# 思路解析
考虑使用**贪心**算法。

显然，我们可以通过排序 $A_i$ 与 $B_i$ 的差值，来比较物理、生物哪个好。若这个差值大，则物理要比生物好；若这个差值小，则生物要比物理好。但如果差值相同，我们则按照物理成绩来排序，来保证序列的单调性。

然后计算总和，即可得出答案。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct node {
    int A, B, C;
    bool operator<(const node& other) const {  // 重载<运算符
        if (C != other.C) {
            return C > other.C;
        }
        return A > other.A;
    }
} s[N];
int n, a, b, ans;
signed main() {
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i].A);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i].B);
    }
    for (int i = 1; i <= n; i++) {
        s[i].C = s[i].A - s[i].B;
    }
    sort(s + 1, s + 1 + n);         // 结构体排序
    for (int i = 1; i <= a; i++) {  // 前a个物理成绩好
        ans += s[i].A;
    }
    for (int i = n; i >= n - b + 1; i--) {  // 倒数b个生物成绩好
        ans += s[i].B;
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：JYX0924 (赞：0)

首先，我们可以给 $A_{i}-B_{i}$ 从小到大排个序，则数组中靠前的位置的人生物成绩相对高，因此让数组中前 $b$ 个人参加生物竞赛，其他人参加物理竞赛。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
#define ll long long 
#define maxn 100005
using namespace std;
struct node {ll cnt,pos;} c[maxn];
ll n,x,y,a[maxn],b[maxn],ans;

bool cmp(node t,node tt) {return t.cnt<tt.cnt;}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) c[i].cnt=a[i]-b[i],c[i].pos=i;
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=y;i++) ans+=b[c[i].pos];
	for(int i=y+1;i<=n;i++) ans+=a[c[i].pos];
	cout<<ans;
	return 0;
}
```
谢谢大家！！！

---

## 作者：__sxx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10771)
## 题意  
给出 $n$ 个学生的物理和生物成绩，选择 $x$ 个学生参加物理竞赛，$y$ 个学生参加生物竞赛，请问最高的总成绩是多少？
## 思路
将学生物理与生物成绩差从大到小排序，前 $x$ 个学生参加物理竞赛，后 $y$ 个学生参加生物竞赛。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int s;
struct data
{
	int p,l,o;
}a[100005];
bool cmp(data x,data y)
{
	return x.o>y.o;
}
int main()
{
   cin>>n>>x>>y;
   for(int i=1;i<=n;i++)
   {
   	 cin>>a[i].p;
   }
   for(int i=1;i<=n;i++)cin>>a[i].l,a[i].o=a[i].p-a[i].l;
  // for(int i=1;i<=n;i++)cout<<a[i].p<<" ";
   sort(a+1,a+1+n,cmp);
   for(int i=1;i<=x;i++)
   {
   	  s=s+a[i].p;
   }
   for(int i=n;i>=n-y+1;i--)
   {
   	 s=s+a[i].l;
   }
   cout<<s;
  return 0;
}

```

---

