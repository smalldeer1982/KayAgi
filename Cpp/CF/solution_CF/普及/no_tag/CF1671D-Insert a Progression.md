# Insert a Progression

## 题目描述

给你一个 $n$ 个数的序列 $a_1,a_2,...,a_n$，同时给你 $x$ 个正整数 $1,2,...,x$。

你要将这 $x$ 个数插入到序列 $a$ 中，每个数可以插在序列首位，末位以及任意两个元素中间。

设最后得到的序列为 $a'$，定义它的分数为相邻两个元素之间的绝对值之和，也就是 $\sum\limits_{i=1}^{n+x-1}|a_i'-a_{i+1}'|$。

求最小分数。

## 说明/提示

样例 $4$ 组询问（构造不一定唯一）：

- $ \underline{1}, \underline{2}, \underline{3}, \underline{4}, \underline{5}, 10 $
- $ \underline{7}, 7, \underline{6}, \underline{4}, 2, \underline{2}, \underline{1}, \underline{3}, \underline{5}, \underline{8}, 10 $
- $ 6, \underline{1}, 1, \underline{2}, 5, 7, 3, 3, 9, 10, 10, 1 $
- $ 1, 3, \underline{1}, 1, 2, \underline{2}, \underline{3}, \underline{4}, \underline{5}, \underline{6}, \underline{7}, \underline{8}, \underline{9}, \underline{10} $

## 样例 #1

### 输入

```
4
1 5
10
3 8
7 2 10
10 2
6 1 5 7 3 3 9 10 10 1
4 10
1 3 1 2```

### 输出

```
9
15
31
13```

# 题解

## 作者：tuzhewen (赞：7)

## 题意
给定一个数组 $a_1,a_2,\cdots,a_n$ 以及一个数 $x$，让你将 $1,2,\cdots,x$ 这 $x$ 个数字插入这个数组，可以插入到最前面，最后面和任意两数之间，令新的数组为$a_i'$。要求你最小化 $\sum\limits_{i=1}^{n+x-1}|a_i'-a_{i+1}'|$ 的值

## 思路
我们看一眼样例解释，第一个想到的就是：如果 $1,2,\cdots,x$ 中有与 $a_i$ 重复数字，那么这些重复的数字对答案**不产生影响**。比如：
`6 5 4` 和 `6 5 5 4` 。我们发现插入 $5$ 之后答案并没有造成影响。

进一步的，我们又可以发现，如果一个数字在 $[l,r]$ 的范围内，我们把这个数字插入 $l,r$ 之间，它对答案同样**不产生影响**。比如 `1,5` 与 `1,2,3,5`，这两个数组计算出来的结果是一样的，这利用的就是绝对值的性质。我们令 $a$ 数组中的最大最小为 $max$ 和 $min$，在这个结论的基础上，我们发现，$1,2,\cdots,x$ 中在 $[min,max]$ 这个范围内的数字对答案也不产生影响。

所以说，我们只要考虑把 $1,2,\cdots,min-1$ 和 $max+1,max+2,\cdots,x$ 这些数字插入到 $a$ 中，由于 $1,x$  也会在最终的 $a'$ 中，所以除了 $1,x$ ，剩下的数字也可以不考虑（由于上面的结论），我们只需要考虑将 $1,x$ 两个数插入在 $a$ 的哪里就好了，这样就大大简化了题目。

一切有关 $1,min$ 和 $x,max$ 的大小讨论，都写在下面了。很显然的，如果 $min=1$，那么我们不用考虑 $1$ 的插入，$max>=x$，我们不用考虑 $x$ 的插入。

## 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
#define fi first
#define se second
const int INF=0x7f7f7f7f,N=2e5+5;
void rd(int &num) {
	num=0;
	int k=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') k=-1,ch=getchar();
	while(ch<='9'&&ch>='0') {
		num=num*10+ch-'0';
		ch=getchar();
	}
	num*=k;
}
int T,n,x;
int a[N];
il void solve() {
	rd(n),rd(x);
	int minn=INF,maxn=-INF;
	ll ans=0;
	F(i,1,n) {
		rd(a[i]);
		minn=min(minn,a[i]);
		maxn=max(maxn,a[i]);
	}
	F(i,1,n-1) ans+=abs(a[i+1]-a[i]);//计算出原来数组的答案
	if(minn>1) {//1会对答案产生影响
		int res1=min(a[1]-1,a[n]-1);
		F(i,2,n) res1=min(res1,a[i]+a[i-1]-2-abs(a[i]-a[i-1]));//循环，寻找把1放在哪里得到的答案最小
        	//res1计算的是1对答案的最小贡献
		ans+=res1;
	}
	if(x>maxn) {//x会对答案产生影响
		int res2=min(x-a[1],x-a[n]);
		F(i,2,n) res2=min(res2,2*x-a[i]-a[i-1]-abs(a[i]-a[i-1]));//循环，寻找把x放在哪里答案最小
        	//res2计算的是x对答案的最小贡献
		ans+=res2;
	}
	printf("%lld\n",ans);
}
int main() {
	rd(T);
	while(T--) {
		solve();
	}
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：4)

## 思路
这题好水，看到题目就有思路了。

首先要明确一件事情，就是插入的这 $x$ 个正整数是无法减小 $a$ 序列的分数的，所以我们要想方设法把这 $x$ 个正整数造成的影响**减小**。

先看一个例子：

若 $a$ 序列为 $1,4$ 且 $x=3$

我们可以得到的最优序列为 $1,1,2,3,4$

发现了吗？我们可以把 $2$ 到 $x-1$ 中的所有数放在 $1$ 和 $x$ 的中间，这样 $2$ 到 $x-1$ 就**对答案没有任何影响**。我们**只要**考虑 $1$ 和 $x$ 这两个数即可，那么这题就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[211100],y[211000];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;cin>>t;
	while (t--){
		int n,x;cin>>n>>x;
		for (int i=1;i<=n;i++) cin>>a[i];
        int ans=0,mina=a[1],maxx=a[1],cx=min(abs(x-a[1]),abs(x-a[n]));
        int cy=min(abs(1-a[1]),abs(1-a[n]));
		for (int i=2;i<=n;i++){
        	maxx=max(maxx,a[i]);
		    mina=min(mina,a[i]);
        	ans+=abs(a[i]-a[i-1]);
        }
        for (int i=2;i<=n;i++)
            cx=min(cx,abs(x-a[i-1])+abs(x-a[i])-abs(a[i]-a[i-1])),
            cy=min(cy,abs(1-a[i-1])+abs(1-a[i])-abs(a[i]-a[i-1]));
		if (x>maxx) ans+=cx;
        if (mina>1) ans+=cy;
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：Henry_C (赞：1)

# 题意
$\qquad$给定 $n(1 \le n\le 2 \cdot 10^5)$ 个整数 $a_1,a_2,...,a_n(1 \le a_i \le 2 \cdot 10^5)$ ，以及整数 $x(1 \le x \le 2 \cdot 10^5)$ 。定义数列的得分为相邻两个数差值的累加 $\text{score}=\sum_{i=2}^n {\lvert a_i-a_{i-1} \rvert}$ 。将 $1,2,...,x$ 全部插入 $a_1,a_2,...,a_n$ 中，可以选择任意位置插入，求插入后的最小 $\text{score}$ 值？
# 解题思路
$\qquad$推论：插入一个数 $s$ ,如果 $a_l \le s \le a_r$ ，则插入 $s$ ,对 $\text{score}$ 的影响为0。

$\qquad$证明：1. 当 $l+1=r$ ，显然插入 $s$ 不改变 $\text{score}$ 。

$\qquad \qquad \ \ \ \ $ 2. 当 $r-l \ge 2$ ，在 $l$~$r$ 中取位置 $k$ ,若 $a_k \ge s$ , 则可以继续在 $l$~$k$ 中找插入 $s$ 的位置；若 $a_k \le s$ ,则可以在 $k$~$r$ 中找插入 $s$ 的位置。由于 $k$ 可以是 $l$~$r$ 的任意位置，因此总是能找到一处相邻的位置插入 $s$ ，使得插入 $s$ 不改变 $\text{score}$。

$\qquad$因此只需要考虑插入 $1$ 和 $x$ ,其他 $2$~$x-1$ 的插入是不影响 $\text{score}$ 的。

$\qquad$插入一个数 $s$ 到 $a_i,a_{i-1}$ 两项中间，对 $\text{score}$ 的影响为 $d={\lvert {\lvert a_i-a_{i-1} \rvert} - ({\lvert a_i-s \rvert} + {\lvert a_{i+1}-s \rvert}) \rvert}$ ,

$$d = \begin{cases}
0 ,& a_{i-1} \le s \le a_{i} \ \text{or} \ a_{i} \le s \le a_{i-1} \ \text{(1)}\\
2(s-a_i) ,& s \ge a_{i} \ge a_{i-1}  \ \text{(2)} \\
2(s-a_{i-1}) ,& s \ge a_{i-1} \ge a_{i}  \ \text{(3)} \\
2(a_i-s) ,& s \le a_{i-1} \le a_{i}  \ \text{(4)} \\
2(a_{i-1}-s) ,& s \le a_{i} \le a_{i-1} \ \text{(5)} \\
\end{cases}$$

$\qquad$由于总要插入比 $x$ 小的数，因此若 $∃ a_i \ge x$ , 则插入 $x$ 不影响 $\text{score}$ 。

$\qquad$因此插入 $1$ 时，用公式 (4) 计算对 $\text{score}$ 的影响；插入 $x$ 时，用公式 (2) 计算对 $\text{score}$ 的影响，若 $x - a_i \le 0$ ，则插入 $x$ 对 $\text{score}$ 无影响。

$\qquad 1$ 的插入位置在 $a_i$ 序列的最外侧时，使得 $\text{score}$ 分别增加 $a_1-1$ 或 $a_n-1$ ；$x$ 的位置在最外侧时，使得 $\text{score}$ 分别增加 $x-a_1$ 或 $x-a_n$ ,若 $x-a_1 \le 0$ 或 $x-a_n \le 0$ ，则总能找到位置插入 $x$ 对 $\text{score}$ 无影响。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int Nmax = 2e5+5;
int a[Nmax];
LL sum, ans;

int t, n, x;

int main(){
//    freopen("1.in","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--){
        cin >> n >> x;
        LL sum = 0;
        for(int i=1; i<=n; i++){
            cin >> a[i];
            if(i>=2)
                sum += abs(a[i]-a[i-1]);
        }

        int b1 = min(a[1]-1, a[n]-1);
        int bX = min(x-a[1], x-a[n]);
        for(int i=1; i<=n; i++){
            b1 = min(b1, (a[i]-1)<<1);
            bX = min(bX, (x-a[i])<<1);
        }
        if(bX<0) bX = 0;
        sum += b1 + bX;
        cout << sum << endl;
    }
    return 0;
}
```


---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1671D](https://www.luogu.com.cn/problem/CF1671D)

* **【解题思路】**

有一个显然的结论：如果已经确定 $1$ 和 $x$ 的位置，则剩下的数一定可以做到无贡献插入。那么只要让这两个数贡献最小即可。证明显然。

暴力查找位置即可。$\mathrm O(n)$。

* **【代码实现】**

```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> nums;

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		nums.clear();
		int cnt,tmp,target;
		long long ans=0;
		cin>>cnt>>target;
		for(int i=0;i<cnt;i++)
			cin>>tmp,nums.push_back(tmp);
		int idx,min_val=167772161;
		for(int i=0;i<=cnt;i++)
		{
			if(i==0)
			{
				min_val=nums[0]-1,idx=0;
				continue;
			}
			if(i==cnt)
			{
				if(min_val>nums[cnt-1]-1)
					idx=cnt,min_val=nums[cnt-1]-1;
				continue;
			}
			if(min_val>2*(min(nums[i-1],nums[i])-1))
				idx=i,min_val=2*(min(nums[i],nums[i-1])-1);
		}
		min_val=167772161;
		nums.insert(nums.begin()+idx,1);
		for(int i=0;i<=cnt+1;i++)
		{
			if(i==0)
			{
				min_val=abs(nums[0]-target),idx=0;
				continue;
			}
			if(i==cnt+1)
			{
				if(min_val>abs(nums[cnt]-target))
					idx=cnt+1,min_val=abs(nums[cnt]-target);
				continue;
			}
			if(min_val>abs(nums[i-1]-target)+abs(nums[i]-target)-abs(nums[i]-nums[i-1]))
				idx=i,min_val=abs(nums[i-1]-target)+abs(nums[i]-target)-abs(nums[i]-nums[i-1]);
		}
		nums.insert(nums.begin()+idx,target);
		for(int i=0;i<nums.size()-1;i++)
			ans+=abs(nums[i]-nums[i+1]);
		cout<<ans<<'\n';
	}
 	return 0;
}


```

---

