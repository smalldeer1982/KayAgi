# Harder Problem

## 题目描述

给定一个正整数序列，若一个正整数在该序列中出现最多次，则称其为该序列的众数（ mode ）。例如，序列 $[2,2,3]$ 的众数为 $2$ 。 $9$ ， $8$ 或 $7$ 的任意一个都可以被认为是序列 $[9,9,8,8,7,7]$ 的众数。

你给了 UFO 一个长度为 $n$ 的数组 $a$ 。为了感谢你， UFO 决定构造一个长度也为 $n$ 的数组 $b$ ，使得对于所有 $1 \leq i \leq n$ ，$a_i$ 是序列 $[b_1, b_2, …, b_i]$ 的众数。

然而， UFO 不知道怎么构造数组 b ，因此你需要帮助她。注意：构造的数组 b 中的元素 $b_i$ 需满足 $1 \leq b_i \leq n$ 。

## 说明/提示

对第 2 组测试样例正确性的证明：

- 当 $i = 1$ 时， $1$ 是 $[1]$ 唯一的众数；
- 当 $i = 2$ 时， $1$ 是 $[1, 1]$ 唯一的众数；
- 当 $i = 3$ 时， $1$ 是 $[1, 1, 2]$ 唯一的众数；
- 当 $i = 4$ 时， $1$ 或 $2$ 均为 $[1, 1, 2, 2]$ 的众数。由于 $a_i = 2$ ，因此这个数组是有效的。

## 样例 #1

### 输入

```
4
2
1 2
4
1 1 1 2
8
4 5 5 5 1 1 2 1
10
1 1 2 2 1 1 3 3 1 1```

### 输出

```
1 2
1 1 2 2
4 5 5 1 1 2 2 3
1 8 2 2 1 3 3 9 1 1```

# 题解

## 作者：JimmyQ (赞：4)

# CF2044D Harder Problem
## 思路
构造一个 $1\sim n$ 都出现了一次的数列（这样每个数都是众数了），然后只要保证在数组 $a$ 里面出现了的数在最前面就好了。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
long long t,vis[N],cnt,n,a[N];
int main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis)),cnt=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			if(vis[a[i]]==1) cnt++;
			else{
				vis[a[i]]=1;
				cout<<a[i]<<" ";
			}
		}
		for(int i=1;i<=n;i++){
			if(vis[i]!=1) cout<<i<<" ";
		}
	}
}
```

[AC记录](https://codeforces.com/contest/2044/submission/299347614)

---

## 作者：如履薄冰 (赞：3)

# 思路
我们只需要让每一个数都只出现一次，使每个数都成为众数。我们还要将出现过的数都标记一下，最后再输出没有标记过的数，这是因为数列中可能会有数重复。
# 代码
[亲测AC](https://codeforces.com/contest/2044/submission/301373477)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1100000];
signed main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        int cnt=0;
        map<int,bool> vis;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            if(vis[a[i]]){
                cnt++;
                continue;
            }
            vis[a[i]]=true;
            cout<<a[i]<<" ";
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==false){
                cout<<i<<" ";
            }
        }
    }
    return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：2)

# presafe
构造题~~
# problem
[题目传送门](/problem/CF2044D)

给你一个数组 $a$，让你构造一个数组 $b$，使得对于每个 $1\le i\le n$，$b$ 数组的前 $i$ 个元素的众数是 $a_i$。
# solution
此题不用太麻烦~~考场上被硬控 40 分钟~~，只需要构造一个排列即可，排列里每个元素都出现了 $1$ 次，那么每个数都是众数了。
# code
~~简单易懂~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
set<int> st;
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) st.insert(i);
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    if (st.count(x)) {
      cout << x << ' ';
      st.erase(x);
    } else {
      int tmp;
      for (int i : st) {
        tmp = i;
        break;
      }
      cout << tmp << ' ';
      st.erase(tmp);
    }
  }
  cout << '\n';
  st.clear();
}
int main() {
  for (cin >> t; t--; solve())
    ;
  return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 思路
构造题，直接让每个数只出现一次，这样每个数都是众数。而且在前面输入的就先输出，这样是最合理的。直接模拟即可
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,t,x;
bool vis[N];
signed main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));//注意初始化 
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			if(!vis[x]){ //之前没出现过就直接输出 
				vis[x]=1;
				cout<<x<<' ';
			}
		}
		for(int i=1;i<=n;i++){
			if(vis[i]!=1) //一直没出现过就在后面输出 
				cout<<i<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：ztd___ (赞：1)

大致题意：

给定数组 $a$，求构造一个数组 $b$，使得对于所有 $1 \le i \le n$，$b_i$ 为序列 $[b_1,b_2,b_3,\dots,b_i]$ 的众数。

这里的众数可能有不止一个。

### 分析
由题目的定义，容易知道：

如果在一个序列中，所有数出现的次数相同，那么它们就都是众数。

因为 $1 \le a_i \le n$，所以 $1 \le b_i \le n$。

因此可以构造一个 $n$ 的排列。

这样对于所有 $1 \le i \le n$，$i$ 在序列 $[b_1,b_2,b_3,\dots,b_i]$ 中的出现次数都为 $1$。

此时，对于所有 $1 \le i \le n$，$b_i$ 都为序列 $[b_1,b_2,b_3,\dots,b_i]$ 的众数。

代码就非常好写了：

首先，对于所有 $1 \le i \le n$，存在 $2$ 种情况：

- $a_i$ 在 $a$ 中仅仅出现了这一次。  
  此时直接输出 $a_i$。  
  否则在序列 $[b_1,b_2,b_3,\dots,b_i]$ 中，数字 $a_i$ 就没有出现，也不可能成为众数。
  
- $a_i$ 在 $a$ 中不止出现了这一次。  
  此时输出一个 $a$ 里面没有出现的数，占个位置即可。  
  如果输出的是 $a$ 里面出现过的数，有可能这个数字在后面会成为唯一的众数，不好判断。

对于两种情况的实现：

- 判断 $a_i$ 在 $a$ 中是否仅仅出现了这一次，可以用一个桶标记一下。

- 对于第二种情况，可以将 $a$ 里面没有出现的数存起来，碰见需要占位的就输出一个。  
  这里输出的数字同样不重复。所以用一个指针 $cnt$ 记录之前已经输出了几个没有出现的数，这次就输出下一个。

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+55;
int n,a[N],b[N],c[N],cnt;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		memset(b,0,sizeof(b));//多测清空
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[a[i]]++;//桶
		}
		cnt=0;//多测清空
		for(int i=1;i<=n;i++){
			if(b[i]==0) c[++cnt]=i;//没出现过的数
		}
		memset(b,0,sizeof(b));//桶重复利用
		for(int i=1;i<=n;i++){
			if(!b[a[i]]) cout<<a[i]<<" ";//情况1，前面未出现过，直接输出
			else cout<<c[cnt--]<<" ";//情况2，前面出现过，用没出现过的数字占位
			b[a[i]]++;
		}
		cout<<"\n";
	}
	return 0;
}
```
应该还算是比较简洁的。

---

## 作者：_yang_yi_bo_ (赞：1)

一眼题。

容易证明，我们可以将数 $1$ 到 $n$ 之间的重新排列，使得答案正确，因为对于所有 $a_i$ 都保证 $1 \le a_i \le n$，所以只要保证排列 $b$ 中每个 $a_i$ 都在 $b_1,b_2,b_3 \dots b_i$ 中出现过即可。

怎么排列呢？对于下标 $i$，若 $a_i$ 在之前的排列中出现过，可以任意输出一个数，否则输出 $a_i$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,a[200005];
bool vis[200005];
void check(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        q.push(i);
        vis[i]=0;
    }for(int i=1;i<=n;i++){
        if(!vis[a[i]]){
            cout<<a[i]<<" ";
            vis[a[i]]=1;
        }else{
            while(vis[q.front()]){
                q.pop();
            }cout<<q.front()<<" ";
            vis[q.front()]=1;
        }
    }cout<<"\n";
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }check();
    }
    return 0;
} //asdasd
```

---

## 作者：sccc_ (赞：1)

## Solution

一道简单的构造题。

对于 $b_i$，我们有两种判断：
- 如果 $a_i$ 在 $b_i$ 出现过，把 $b_i$ 设为范围是 $1$ 到 $n$ 并且未在 $a_i$ 中出现过的数字。
- 否则，直接把 $b_i$ 设为 $a_i$ 即可。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n;
int a[200005];
int b[200005];
int cnt[200005];
bool vis[200005];
set<int> s;
int pos;

void work()
{
    pos = 0;
    s.clear();
    memset(vis, 0, sizeof(vis));
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i], vis[a[i]] = 1;
    for (int i = 1; i <= n; i ++)
        if (vis[i] == 0)
            cnt[++ pos] = i;
    int idx = 0;
    for (int i = 1; i <= n; i ++) 
    {
        if (s.count(a[i]) == 0) 
        {
            s.insert(a[i]);
            b[i] = a[i];
        } 
        else 
        {
            b[i] = cnt[++ idx];
        }
    }
    for (int i = 1; i <= n; i++)
        cout << b[i] << ' ';
    cout << '\n';
}

signed main() 
{
    int t;
    cin >> t;
    while (t --) 
    {
        work();
    }
    return 0;
}
```

---

## 作者：ohjun (赞：1)

## 思路分析
因为 $1 \le a_i \le n$，不难发现只要另 $1 \sim n$ 的所有数都只出现一次，此时每个数都是众数，满足题目条件。综上，对于每个 $a_i$ 如果在 $b$ 中没有出现过就将 $b_i$ 的值设为 $a_i$，否则随便放一个没出现过的 $1 \sim n$ 的数即可。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int t, n;
bool vis[maxn];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		int now = 1, num;
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= n; i++)
		{
			cin >> num;
			while(now <= n && vis[now])
				now++;
			if(vis[num])
			{
				cout << now << ' ';
				vis[now] = true;
			}
			else
			{
				cout << num << ' ';
				vis[num] = true;
			} 
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：wawatime1 (赞：1)

### 题目大意
给定数组 $a$，要构造数组 $b$，使 $a$ 中每个元素 $a_i$ 是 $b$ 中前 $i$ 个元素 $[b_1, b_2, …, b_i]$ 的众数，且 $1 ≤ b_i ≤ n$。
### 解题思路
**初始化：**

当 $i = 1$ 时，直接让 $b_1 = a_1$，因为单个元素就是它自己的众数。同时，用数组 $count$ 记录每个数出现次数，此时 $count_{a_1}=1$，最大出现次数 $mxc = 1$。

**构造：**

若 $a_i$ 出现次数小于 $mxc$：找出现次数最少的数作为 $b_i$，更新其出现次数。若 $a_i$ 加上这次出现能成为最大次数，就更新 $mxc$。这样做是为了让 $a_i$ 有机会成为众数。

若 $a_i$ 出现次数大于等于 $mxc$：直接让 $b_i = a_i$，更新其出现次数并更新 $mxc$。因为它本身出现次数已满足或超过当前众数出现次数，可直接加入。

---

## 作者：yr409892525 (赞：1)

## CF2044D 题解
这是一道构造题。          
因为我们要让 $a_i$ 中的每一个数都成为众数。             
不妨让每一个 $a_i$ 在 $b$ 序列中存在的个数相似。             
先把 $a_i$ 去重。              
把 $a$ 数组当作一个循环，重复出现在 $b_i$ 中。              
但是有一个问题，就是有可能这个循环还没有结束，导致不是每一个数都是众数。       
这时可以提前让这个数存在，标记一下就可以了。      
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,m;
int a[N];
int b[N];
int t[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int q;
    cin>>q;
    while(q--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            b[i]=a[i];
            t[a[i]]=0;
        }
        sort(a+1,a+n+1);
        int m=unique(a+1,a+n+1)-a-1;
        int k=1;
        for(int i=1;i<=n;i++){
            if(t[b[i]]==0 && a[k]!=b[i]){
                cout<<b[i]<<" ";
                t[b[i]]=1;
            }else{
                while(t[a[k]] && k<=m) k++;
                if(k<=m){
                    cout<<a[k]<<" ";
                    t[a[k]]=1;
                }else{
                    for(int j=1;j<=m;j++) t[a[j]]=0;
                    k=1;
                    if(a[k]==b[i]){
                        cout<<a[k]<<" ";
                        t[a[k]]=1;
                    }else{
                        cout<<b[i]<<" ";
                        t[b[i]]=1;
                    }
                }
            }
        }
        cout<<"\n";
    }
	return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：0)

任意一个出现次数最多的数都可以是众数，那么我们让每个数都只出现一次即可满足条件。

需要注意的是，在 $a$ 数组里先出现的数也要在 $b$ 数组里先出现，这样才能满足 $a_i$ 在 $b_{1\dots i}$ 中出现过。

一开始按顺序输出在 $a$ 数组中出现过的数并标记，然后再输出剩下的数把 $b$ 数组填满即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) f[i]=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			if(!f[x]) f[x]=1,cout<<x<<" ";
		}
		for(int i=1;i<=n;i++)
			if(!f[i]) cout<<i<<" ";
		cout<<"\n";
	}
    return 0;
}

```

---

## 作者：wflhx2011 (赞：0)

注意到，题目中说若多个数出现次数最多，这些数都可以被视为众数。

所以，考虑让每个数都出现一次，使得所有数都是众数，自然满足题意。

因为要求 $1\le b_i \le n$，所以对于 $1$ 到 $n$，将没在 $a$ 数组出现的数处理出来。

输出答案时，若这个数是第一次出现，就输出并标记，否则将没出现的数依次输出。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],f[200005],b[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,cnt=0;
		cin>>n;
		memset(f,0,sizeof(f));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			f[a[i]]=1;
		}
		for(int i=1;i<=n;i++)	
			if(!f[i])
				b[++cnt]=i;
		cnt=0;
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++)
			if(f[a[i]])
				cout<<b[++cnt]<<" ";
			else
				cout<<a[i]<<" ",f[a[i]]=1; 
		cout<<endl;
	}
	return 0;
 } 
```

---

## 作者：lhs_chris (赞：0)

# 思路
题目明确表示当序列的数字的出现次数相同时，这些数字都是该序列的众数。

那么我们可以想到让所有数字都只出现一次，那么所有数字都是众数。对于输入序列中重复出现的数字，我们就在 $1 \sim n$ 之中从前往后寻找输入序列之中没有的数字，输出，然后标记掉。
# 代码
```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=3e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int t;
int n;
int a[N];
bool flag[N];
bool flag2[N];
int ans[N];
int nxt; 
int maxx;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		nxt=1;
		memset(flag,0,sizeof flag);
		memset(flag2,0,sizeof flag2);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			flag[a[i]]=1;
		}
		for(int i=1;i<=n;i++)
		{
			if(flag2[a[i]]==0)
			{
				printf("%d",a[i]);
				flag2[a[i]]=1;
			}
			else
			{
				while(flag[nxt]!=0)
				{
					nxt++;
				}
				flag[nxt]=1;
				printf("%d",nxt);
			}
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [Harder Problem](https://www.luogu.com.cn/problem/CF2044D) | Codeforces [D. Harder Problem](https://codeforces.com/contest/2044/problem/D)

更佳的阅读体验：[CF2044D 题解](https://blog.ryanli.top/index.php/archives/235/)

---

**简要题意**：给定序列 $a$，尝试构造一个序列 $b$，使得 $a$ 中每个元素 $a_i$ 都是 $b$ 中前 $i$ 个数构成的序列的众数（mode），且 $b$ 中每个元素 $b_i$ 都满足 $b_i \in [1, n]$。

由众数的定义，可以想到一个序列中可以有多个众数，所以当 $[1, n]$ 中的每个数都各出现一次时，每个数都是序列 $b$ 的众数。

此时，问题转化为构造一个 $[1, n]$ 的排列。

要保证 $a$ 中每个元素 $a_i$ 都是 $b$ 中前 $i$ 个数构成的序列的众数，只需要在 $a_i$ 第一次出现的位置输出 $a_i$，其余的位置输出任意一个 $a$ 中没有出现过的数即可。

```cpp
#include <iostream>
#include <bitset>
using namespace std;

const int N = 2e5 + 10;
int t, n, a[N], ans[N];
bitset<N> vis;
basic_string<int> num, inum;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        num.clear(), inum.clear(), vis.reset();
        fill(ans + 1, ans + n + 1, 0);
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i], vis.set(a[i]);
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) num += i;
            else inum += i;
        } vis.reset();
        int pos = 0;
        for (int i = 1; i <= n; ++i) {
            if (!vis[a[i]]) vis.set(a[i]), ans[i] = a[i];
            else ans[i] = inum[pos++];
        } for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
    } return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# Solution
## 题目分析
如果一个数出现的次数等于这个序列中出现次数最多的数，那么我们称这个数为这个序列的 mode，由此定义的众数可能就不止一个。  
给定一个长度为 $n$ 的序列 $a$，要求构造输出一个序列 $b$，使 $a_i$ 是数列 $[b_1,b_2,…,b_i]$ 的 mode。
## 思路分析
由于这样定义的众数可能不止一个，可以使输出的序列 $b$ 中每一个数仅出现一次，这样 $b$ 中的每一个数都是数列 $b$ 的 mode。  
对于 $a$ 中先出现的数，如果之前没有出现过，则直接输出，以免防止 $b$ 中不存在这个数的状态。  
之后遍历 $1$ 到 $n$ 中所有数，如果该数没有出现过，且 $b$ 数组尚未填完，输出该数，此数不会对 $b$ 数列的 mode 作影响。    
完成操作之后 $a_i$ 必定只在 $b$ 中出现一次，且对于对应的 $b_j$，$1\le i \le j \le n,a_i \le n,b_i\le n$ 必定成立。
## 代码实现

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
int vis[200005];
void solve() 
{
	int n;
	cin>>n;
	ffor(i,1,n) vis[i]=0;
	int sum=0;
	ffor (i,1,n) {
		int x;
		cin>>x;
		if (!vis[x]) cout<<x<<" ",sum++;
		vis[x]=1;
	}
	for (int i=1,j=1;i<=n-sum;j++) {
		if (!vis[j]) {
			cout<<j<<" ";
			i++;
		}
	}
	cout<<'\n';
}
int main()
{
	int T;
	cin>>T;
	while (T--) solve();
	return 0;
}
```
似乎是题解区里最简单的做法。

---

## 作者：Gongyujie123 (赞：0)

## [CF2044D Harder Problem](https://www.luogu.com.cn/problem/CF2044D) 题解
### 1. 思路分析
这是一道很简单的构造题。

由题可知，要想答案正确，序列 $a$ 中的每一个数必须要在序列 $b$ 中出现。

对于 $b_i$（$1 \le i \le n$），我们可以做两个操作：  

1. 如果 $a_i$ 在 $b_1,b_2,...,b_i$ 中出现过，就输出一个 $[1,n]$ 中没有出现过的数。
2. 如果 $a_i$ 在 $b_1,b_2,...,b_i$ 中没有出现过，就输出 $a_i$。

### 2. AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[200005],b[200005];
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,o=1;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=0;
		}
		for(int i=1;i<=n;i++){
			if(b[a[i]]==0){
				cout<<a[i]<<' ';
				b[a[i]]=1;
			}else{
				int p=o;
				while(p<n&&b[p]){
					p++;
				}
				cout<<p<<' ';
				b[p]=1;
				o=p; //小优化 
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

因为要满足 $a _ {i}$ 是 $b _ {1} \sim b _ {i}$ 的众数，而多个相同的最大值均为众数。所以我们可以使所有已经出现过的 $a _ {i}$ 在 $b$ 中恰好出现一次，而重复的位置填一个 $[1,n]$ 中还没填的数就好了。

### Code

```cpp
#include <bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;

constexpr int MAXN = 2e5 + 24;
int T;
int n,a,b[MAXN];
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
    {
        cin >> n;
        gp_hash_table<int,bool> apr;
        fill(b + 1,b + n + 1,0);
        for(int i = 1;i <= n;i++)
        {
            cin >> a;
            if(apr[a])
                continue;
            else
                b[i] = a,apr[a] = 1;
        }
        int p = 1;
        for(int i = 1;i <= n;i++)
        {
            if(!b[i])
            {
                while(apr[p])
                    ++p;
                cout << p << " ";
                apr[p] = 1;
            }
            else
                cout << b[i] << " ";
        }
        cout << "\n";
    }
}
```

---

## 作者：lixianyuan (赞：0)

# 题意
## 传送门
[题目链接（洛谷）](https://www.luogu.com.cn/problem/CF2044D)\
[题目链接（Codeforces）](https://codeforces.com/problemset/problem/2044/D)
## 翻译
### 题目描述
给定一个正整数序列，如果一个正整数出现的次数达到了所有正整数出现的最大次数，那么这个正整数就称为序列的一种“众数”。例如，$[2,2,3]$ 的“众数”为 $2$ 。$9$、$8$ 或 $7$ 中的任何一个都可以被认为是序列 $[9,9,8,8,7,7]$ 的“众数”。\
您给 UFO 一个长度为 $n$ 的数组 $a$。为了感谢您，UFO 决定构建另一个长度为 $n$ 的数组 $b$，使 $a_i$ 成为所有 $1 \leq i \leq n$ 序列 $[b_1, b_2, \ldots, b_i]$ 的“众数”。\
你必须帮助 UFO 构造数组 $b$。
# 思路
先构造 $1$ 到 $n$ 的数组，再按输入确定顺序，剩下的数直接加到数组后面不影响结果。\
本题思维和代码难度均不高，建议评橙。
# Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define itn int
#define icn cin
#define endl "\n"

using namespace std;

const int N = 2e5 + 10;

int n, len;
int a[N], b[N];
map<int, int> m, c;

void work() {
	m.clear();
	len = 0;		//多组数据要记得初始化 
	cin >> n;
	for (int i = 1; i <= n; i++) {
		c[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (m[a[i]] != 1) {		//去重并记录剩下的数字 
			m[a[i]] = 1;
			c[a[i]] = 0;
			b[++len] = a[i];
		}
	}
	for (int i = 1; i <= len; i++) {
		cout << b[i] << " ";
		b[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (c[i]) {
			cout << i << " ";
		}
	}
}

int main(){
	int _; cin >> _;		//T组数据 
	while (_--) {
		work();
		cout << endl;
	}
	return 0;
}
```
## AC 记录
![](https://cdn.luogu.com.cn/upload/image_hosting/409uopvb.png)

---

## 作者：Ak_hjc_using (赞：0)

洛谷题目：[CF2044D](https://www.luogu.com.cn/problem/CF2044D) \
CF题目：[CF2044D](https://codeforces.com/problemset/problem/2044/D)

### 题目翻译

给定一个正整数序列，如果一个正整数出现的次数达到了任何正整数出现的最大次数，那么这个正整数就称为序列的一种模式。例如，$[2,2,3]$ 的模式为 $2$。$9$、$8$ 或 $7$ 中的任何一个都可以被认为是序列 $[9,9,8,8,7,7]$ 的模式。

您给 UFO 一个长度为 $n$ 的数组 $a$。为了感谢你，UFO 决定构造另一个长度为 $n$ 的数组 $b$，使 $a_i$ 成为所有 $1 \leq i \leq n$ 序列 $[b_1, b_2, \ldots, b_i]$ 的模式。

但是，UFO 不知道如何构造数组 $b$，所以你必须帮助她。请注意，对于所有 $1 \leq i \leq n$，数组必须保持 $1 \leq b_i \leq n$。

### 思路
一道很水的构造题。

由题意得知，**如果只有一个数组，其中所有的元素都是唯一的，那么每个数都是这个数组的一个模式**。

所有我们构造的策略就是：
1. 对于每个元素 $a_{i}$，如果这个值以前在数组中出现过（可以使用 set 或 map 来判断），就可以将 $b_{i}$ 设为在数组 $a$ 中没有出现过的一个数字。
2. 否则，就直接将 $b_{i}$ 设为 $a_{i}$ 即可。

### 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N], b[N], n, cnt[N];
bool vis[N];
set<int> st;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        st.clear();
        memset(vis, 0, sizeof(vis));
        cin >> n;
        int idx = 0;
        for (int i = 1; i <= n; i++)
            cin >> a[i], vis[a[i]] = 1;
        for (int i = 1; i <= n; i++)
            if (vis[i] == 0)
                cnt[++idx] = i;
        int j = 1;
        for (int i = 1; i <= n; i++) {
            if (st.count(a[i]) == false) {
                st.insert(a[i]);
                b[i] = a[i];
            } else {
                b[i] = cnt[j];
                j++;
            }
        }
        for (int i = 1; i <= n; i++)
            cout << b[i] << ' ';
        cout << '\n';
    }
    return 0;
}

```

---

## 作者：guoxinda (赞：0)

## 思路
因为众数可以有多个，所以每个输出一遍就行了。\
遍历一遍，先见到的就先输出变成众数，然后为了保证 $n$ 个数全部出现，把 $a$ 数组中没有出现的输出到后面。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m;
int main(){
	cin>>t;
	while(t--){
		map<int,int>ma;//新建map
		vector<int>v;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>m;
			if(!ma[m]){//第一次出现,使得对于所有1<=i<=n,ai是序列[b1,b2,...,bi]的众数。
				ma[m]=1;
				cout<<m<<" "; 
			}
		}for(int i=1;i<=n;i++){//必须保证所有1~n的数都有 
			if(!ma[i]){//原来没有 
				cout<<i<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
} 
```

---

