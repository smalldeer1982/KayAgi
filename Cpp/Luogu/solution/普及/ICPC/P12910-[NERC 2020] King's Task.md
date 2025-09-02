# [NERC 2020] King's Task

## 题目描述

勇敢的骑士来到国王面前，请求迎娶公主。国王知道骑士很勇敢，但他还想确认骑士是否足够聪明。于是国王给骑士布置了以下任务：

有一个从 $1$ 到 $2n$ 的数字排列 $p_i$。你可以进行两种操作：

1. 交换 $p_1$ 和 $p_2$、$p_3$ 和 $p_4$、...、$p_{2n-1}$ 和 $p_{2n}$（即相邻两两交换）。
2. 交换 $p_1$ 和 $p_{n+1}$、$p_2$ 和 $p_{n+2}$、...、$p_n$ 和 $p_{2n}$（即前半部分与后半部分对应位置交换）。

任务要求找到将给定排列排序所需的最少操作次数。

实际上骑士并没有那么聪明，但他很有魅力，所以公主请你帮助他完成国王的任务。

## 说明/提示

在第一个样例中，可以通过三次操作将排列排序：
1. 执行操作 1：$3, 6, 5, 2, 1, 4$。
2. 执行操作 2：$2, 1, 4, 3, 6, 5$。
3. 执行操作 1：$1, 2, 3, 4, 5, 6$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
6 3 2 5 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2
3 4 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
0```

# 题解

## 作者：qwqerty (赞：4)

提供一种线性的做法。  

首先对于 $n\bmod2=0$ 的做法是简单的，感性理解一下，将这个排列分为前半段和后半段。在执行操作 $2$ 的时候，都是在同一段内交换，所以前后并不会影响。故最终只会有 $[1,2,3,\dots,2n]$、$[n+1,n+2,n+3,\dots,2n,1,2,3,\dots,n]$、$[2,1,4,3,6,5,\dots,2n,2n-1]$、$[n+2,n+1,n+4,n+3,n+6,n+5\dots,2n,2n-1,2,1,4,3,6,5,\dots,n,n-1]$ 这四种情况有解，需进行的操作数分别为 $0$、$1$、$1$、$2$，打个表应该很容易理解。  

若 $n\bmod2=1$，有一个很显然的结论就是执行完操作 $2$ 后必须执行操作 $1$，执行完操作 $1$ 后必须执行操作 $2$。所以操作方案可以分为以下四种情况：
- 第一次执行操作 $1$，最后一次执行操作 $1$。
- 第一次执行操作 $2$，最后一次执行操作 $1$。
- 第一次执行操作 $1$，最后一次执行操作 $2$。
- 第一次执行操作 $2$，最后一次执行操作 $2$。

这四种情况其实可以变为两种情况，根据操作数的奇偶性来决定。所以可以从排列有序开始，暴力计算 $n$ 在排列中的下标，而 $n$ 在排列中的下标一定是不同的。因为若存在两个有解的排列且 $n$ 在这两个排列中的下标相同同，根据 $n\bmod2=0$ 的方法，将这个排列拆成前后两个部分可以证明这两个排列一定相同。  
所以直接模拟 $n$ 的下标，若 $n$ 的下标和排列中的相同，则记录下当前的操作次数。将操作 $2$ 开始的情况和操作 $1$ 开始的情况各模拟一遍即可。  
难点就来到了判无解，由于排列的置换满足结合律，所以可以用快速幂解决。或者把排列拆分成多个环，依次操作每个环。若最后与排列相同则有解。

$O(n\log n)$ 的快速幂写法：<https://www.luogu.me/paste/9s69w0kx>。  
$O(n)$ 找环写法：<https://www.luogu.me/paste/16s5dxtc>。

---

## 作者：Belia (赞：1)

### 题意：

给定一个长度为 $2n$ 的排列，你可以执行两种操作：

- **操作 1**：交换相邻的两对元素，即交换位置 $(1,2),(3,4),…,(2n−1,2n)$。

- **操作 2**：交换前半部分和后半部分对应位置的元素，即交换位置 $(1,n+1),(2,n+2),…,(n,2n)$。

求将排列变为递增序列 $(1,2,…,2n)$ 的最小操作步数。若无法完成，输出 $−1$。

### 思路：

**经观察不难发现**：**操作 1** 和**操作 2** 都是**可逆**的，且操作序列会形成循环。最小操作序列必然是两种操作交替进行（连续两次相同操作会相互抵消）。

因此我们就可以实现：

**操作 1**：

```cpp
void op1(vector <ll>& a)// 操作 1：相邻两两交换
{
    for(ll i=0;i<a.size();i+=2)
    swap(a[i],a[i+1]);
}
```
**操作 2**：

```cpp
void op2(vector <ll>& a)// 操作 2：前半部分和后半部分对应交换
{
    ll len=a.size()/2;
    for(ll i=0;i<len;i++)
    swap(a[i],a[i+len]);
}
```

……

最后的最后，就是我们的完整代码了（注释已经搞里头了）……

### 代码：


```cpp
#include<bits/stdc++.h>
#define ll long long//#define ll long long你值得拥有
using namespace std;
ll n,ans1,ans2;
void op1(vector <ll>& a)// 操作 1：相邻两两交换
{
    for(ll i=0;i<a.size();i+=2)
    swap(a[i],a[i+1]);
}
void op2(vector <ll>& a)// 操作 2：前半部分和后半部分对应交换
{
    ll len=a.size()/2;
    for(ll i=0;i<len;i++)
    swap(a[i],a[i+len]);
}
bool check(const vector <ll>& a)// 检查排列是否有序
{
    for(ll i=0;i<a.size();i++)
    if(a[i]!=i+1)
	return false;
    return true;
}
ll solve(vector <ll> p,ll fop)
{
    ll cnt=0;
    while(cnt<=4*p.size())
	{
        if(check(p))
		return cnt;
        if(cnt%2==0)
		fop==1?op1(p):op2(p);
        else
		fop==1?op2(p):op1(p);
        cnt++;
    }
    return -1;
}
int main()
{
    cin>>n;
    vector <ll> p(2*n);
    for(auto& x:p)
	cin>>x;
    if(check(p))// 初始即有序，直接输出 0
	{
        cout<<"0\n";
        return 0;
    }
    ans1=solve(p,1),// 模拟序列 A：操作 1 -> 操作 2 -> 操作 1 -> ...
	ans2=solve(p,2);// 模拟序列 B：操作 2 -> 操作 1 -> 操作 2 -> ...
    if(ans1==-1&&ans2==-1)
	cout<<"-1\n";
    else if(ans1==-1)
	cout<<ans2<<"\n";
    else if(ans2==-1)
	cout<<ans1<<"\n";
    else
	cout<<min(ans1,ans2)<<"\n";
    return 0;
}
```
完结撒花~

---

## 作者：3_14 (赞：0)

[**题目传送门**](https://www.luogu.com.cn/problem/P12910)

# 思路

要求通过两种特定操作将给定的排列转换为升序排列，需要找到最少的操作次数。

我们可以使用广搜来遍历所有可能的状态（BFS 适合求解最短路径问题，因为它逐层扩展状态，一旦找到目标状态，当前步数即为最短路径）。

# 代码

```cpp
#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y
#define lb(x) (x&-x)
#define str to_string
using namespace std;
using ll=long long;
const double EPS=1e-6,PAI=acos(-1.0);
const int MAX=3e4+5,mod=1e9+7,MOD=998244353;
vector<int>op1(vector<int>p){// 应用操作1：相邻两两交换
    vector<int>r=p;
    int n=p.size()/2;
    for(int i=0;i<n;i++)swap(r[2*i],r[2*i+1]);// 交换每对相邻元素
    return r;
}
vector<int>op2(vector<int>p){// 应用操作2：前半部分与后半部分对应位置交换
    vector<int>r=p;
    int n=p.size()/2;
    for(int i=0;i<n;i++)swap(r[i],r[i+n]);// 交换前半部分和后半部分对应位置
    return r;
}
string vtos(vector<int>p){// 转换为字符串，用于哈希映射
    string s;
    for(int num:p)s+=str(num)+",";// 将排列转换为字符串，便于记录和比较状态
    return s;
}
int n;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    vector<int>p(2*n);
    for(int i=0;i<2*n;i++)cin>>p[i];// 读取输入排列
    vector<int>t(2*n);// 目标排列：1, 2, 3, ..., 2n
    for(int i=0;i<2*n;i++)t[i]=i+1;
    if(p==t){// 如果初始排列已经有序，直接输出0
        cout<<"0\n";
        return 0;
    }
    queue<pair<vector<int>,int>>q;// BFS队列，存储当前排列和已用步数
    unordered_map<string,int>d;// 哈希表记录已访问的状态及其步数
    q.push({p,0});// 初始状态入队
    d[vtos(p)]=0;// 记录初始状态的步数为0
    int a=-1;// 初始化为-1，表示无法排序
    while(q.size()){
        auto[c,s]=q.front();
        q.pop();
        vector<int>n1=op1(c);
        string n1s=vtos(n1);
        if(!d.count(n1s)){// 如果新状态未访问过
            d[n1s]=s+1;// 记录新状态的步数
            if(n1==t){// 如果达到目标状态
                a=s+1;// 更新答案
                break;// 退出循环
            }
            q.push({n1,s+1});// 新状态入队
        }
        // 和上面基本一致
        vector<int>n2=op2(c);
        string n2s=vtos(n2);
        if(!d.count(n2s)){
            d[n2s]=s+1;
            if(n2==t){
                a=s+1;
                break;
            }
            q.push({n2,s+1});
        }
    }
    cout<<a<<'\n';
    return 0;
}
```

### 时间复杂度

最坏情况下需要遍历所有可能的状态，时间复杂度为 $O \left(\left(2\times n\right)!\right)$，但实际中有剪枝，复杂度会比理论低很多。

[**AC 记录**](https://www.luogu.com.cn/record/221414517)

---

