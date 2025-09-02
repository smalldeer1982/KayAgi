# Inhabitant of the Deep Sea

## 题目描述

$n$ 艘船只开始探索海洋深处。这些船的编号从 $1$ 到 $n$ 并按升序相互跟随，第 $i$ 只船的耐久度是 $a[i]$ 。( $1 ≤ a[i] ≤ 10^9$ )

海妖按特定顺序袭击 $k$ 次船只：首先，它攻击船队的第一艘船只，然后攻击最后一艘，然后再攻击第一艘……依此类推。

海妖的每次攻击都会降低飞船的 $1$ 耐久度。当船舶的耐久性下降到 $0$ ，它就沉没了（而海妖只攻击尚未沉没的船只）。如果所有的船只都沉没了，海妖就没有什么可攻击的了，它就会游走。

给定 $n , k$ 和 $n$ 只船的耐久度，问海妖袭击后有多少艘船被击沉？

## 样例 #1

### 输入

```
6
4 5
1 2 4 3
4 6
1 2 4 3
5 20
2 7 1 8 2
2 2
3 2
2 15
1 5
2 7
5 2```

### 输出

```
2
3
5
0
2
2```

# 题解

## 作者：_ayaka_ (赞：3)

## 思路
此题其实只要想通就十分简单，几乎没有考任何算法。

我们首先可以发现，海怪的攻击是绝对按顺序的，所以我们可以求出海怪攻击两边的次数 $k1$，$k2$。

然后，我们就可以对两边进行一次循环，求出海怪在两边能到达的距离。具体来说，步骤是这样的：
1. 从第 $1$ 艘船往后循环到 $n$，如果海怪攻击的次数 $k1$ 大于等于船的耐久 $a_i$，那就将 $k1$ 减去 $a_i$；反之，将 $a_i$ 减去剩余的 $k1$，就提前结束循环；

1. 同时，我们记录下最远摧毁的船的编号 $h$，并将答案 $ans$ 加上 $h$；

1. 再接着，我们再从 $n$ 往前循环到 $h+1$，然后再次使用第 $1$ 步的方法求出最远到达的距离，加到 $ans$ 上；

1. 最后，输出 $ans$。

然后我们就解决了本题。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,k1,k2,h,a[200005],ans;
signed main() {
	cin>>t;
	while(t--){
		cin>>n>>k;
		k2=k/2;//由于除法是向下取整，海怪又是从前面开始，所以除法用在 k2 上。
		k1=k-k2;
		h=0,ans=0;//记得清零！
		for(int i=1;i<=n;i++) {
			cin>>a[i];
			if(k1>=a[i]){//为了节省一点时间就在读入的同时做了第一遍循环。
				k1-=a[i];
				h=i;
			}else{
				a[i]-=k1;
				k1=0;
			}
		}
		ans=h;
		for(int i=n;i>h;i--){
			if(a[i]<=k2) k2-=a[i],ans++;
			else break;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：2c_s (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1955C)

## 思路

观察到 $1\le k\le 10^{15}$，所以模拟肯定不行。我们考虑用前缀和、后缀和。

读入数据后统计前缀和、后缀和。记录从前面总共要攻击的次数为 $\lceil k/2\rceil$，从后面总共要攻击的次数为 $\lfloor k/2\rfloor$。

之后 $1$ 到 $n$ 循环找前面能攻击掉几个（即前缀和到几为止 $\le\lceil k/2\rceil$）；从 $n$ 到 $1$ 循环找后面能攻击掉几个（即后缀和到几为止 $\le\lfloor k/2\rfloor$）。比较这两个值的和与 $n$，取小者输出。

时间复杂度 $\mathcal{O}(Tn)$。

- **注意**：如果总攻击次数大于等于所有数的和，那么结果为 $n$。

- 有多组测试数据，记得**清空**变量、前缀后缀数组。

- 开 long long。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
long long n,k,a[N],pre[N],suf[N];
int main(){
	int T;
    cin>>T;
	while(T--){
		cin>>n>>k;
		long long ans=0,sum=0;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			sum+=a[i];
		}
		if(k>=sum){//特判。
			cout<<n<<"\n";
			continue;
		}
		for(int i=1;i<=n;++i)pre[i]=pre[i-1]+a[i];
		for(int i=n;i>=1;--i)suf[i]=suf[i+1]+a[i];
		long long head=k/2,tail=k/2;
		if(k%2==1)++head;
		for(int i=1;i<=n;++i){
			if(head<pre[i]){
				ans=i-1;
				break;
			}
		}
		if(head>=pre[n])ans=n;//最后再记录一遍。
		for(int i=n;i>=1;--i){
			if(tail<suf[i]){
				ans+=n-i;
				break;
			}
		}
		if(tail>=suf[1])ans+=n;//最后再记录一遍。
		for(int i=1;i<=n;++i)pre[i]=suf[i]=0;
		cout<<min(n,ans)<<"\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/155211297)

---

## 作者：YZMX (赞：2)

## 题目描述

给出飞船数量 $n$，每艘飞船的耐久 $a_i$。特定的顺序攻击了船只 $k$ 次。先攻击第一艘船，然后是最后一艘，接着又是第一艘，以此类推。每次攻击使飞船降低 $1$ 耐久，当耐久为 $0$ 时沉没，就不再受攻击，求 $k$ 次攻击后击沉的船数量。

## 题目分析

观察到数据 $k$ 的规模很大，不能模拟每次攻击。但是 $n$ 比较小，所以可以想到枚举枚举击沉的船。

简单的想法是判断当前左右两端飞船剩余耐久的大小，然后先击沉耐久小的，但是这样实现非常麻烦，我们想一想更简单的方法。对于总共的 $k$ 次攻击，因为攻击有一定的顺序，所以攻击左右两端的次数我们可以分别得到，攻击左端飞船的次数为 $\lceil k\div2 \rceil$，攻击右端飞船次数为 $\lfloor k\div2 \rfloor$。

那么我们可以从左向右枚举左边攻击可以击沉的船，从右向左枚举右边攻击可以击沉的船，这样得到答案。

注意一点，判断攻击次数是否大于总耐久是必须的，加上这个判断，可以让答案约束在不超过 $n$ 的范围内，从而做到后面的处理不会超过 $n$。

## 代码

```
#include<iostream>
using namespace std;

long long t,n,k,pl,pr,a[200005],sum,ans;

int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=0;i<=n;i++) a[i]=0;// 清空数组
        sum=0;
        ans=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        if(k%2==0) pl=k/2;//计算左边攻击次数
        else pl=k/2+1;
        pr=k/2;//计算右边攻击次数
        if(k>=sum){//特判如果攻击次数大于等于总耐久，那么一定可以击沉全部
            cout<<n<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){//处理从左边攻击
            if(pl<a[i]) break;
            ans++;
            pl-=a[i];
        }
        for(int i=n;i>=1;i--){//从右边攻击
            if(pr<a[i]) break;
            ans++;
            pr-=a[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：yshpdyt (赞：2)

# C
## 题意
长为 $n$ 的序列，可以进行 $k$ 次操作。对于奇数次操作来说，使序列最左边 $-1$，偶数次操作，使序列最右边 $-1$。如果一个位置操作完后为 $0$，那么就删去一个元素，开头右移或末尾左移。

求删除了多少个数。

## Sol
用 $now=0$ 表示现在是奇数次操作，$now=1$ 表示现在是偶数次操作，考虑每次操作**只**清零一个位置，转化问题变成求保留多少个数，让 $l,r$ 表示当前操作的左右端点。

### 对于 $now=0$：
若 $a_l\le a_r$，花费 $2\times a_l-1$ 次操作，进行如下变化：

$$a_r \rightarrow a_r-(a_l-1)$$

$$k\rightarrow k-(2\times a_l-1)$$

$$a_l\rightarrow0$$
 
$$l \rightarrow l+1$$

$$now \rightarrow 1$$

若 $a_r<a_l$，花费 $2\times a_r$ 次操作，进行如下变化：


$$a_l\rightarrow a_l-a_r$$

$$k\rightarrow k-(2\times a_r)$$

$$a_r \rightarrow 0$$

$$r \rightarrow r-1$$
 
$$now \rightarrow 0$$

### 对于 $now=1$：
若 $a_r\le a_l$，花费 $2\times a_r-1$ 次操作，进行如下变化：

$$a_l \rightarrow a_l-(a_r-1)$$

$$k\rightarrow k-(2\times a_r-1)$$

$$a_r\rightarrow0$$
 
$$r \rightarrow l-1$$

$$now \rightarrow 0$$

若 $a_l<a_r$，花费 $2\times a_l$ 次操作，进行如下变化：


$$a_r\rightarrow a_r-a_l$$

$$k\rightarrow k-(2\times a_r-1)$$

$$a_l \rightarrow 0$$

$$l \rightarrow l+1$$
 
$$now \rightarrow 1$$

### 特别的，对于 $l=r $：

花费 $a_l$，如下变化并且结束循环。：

$$a_l\rightarrow0$$

$$k\rightarrow k-a_l$$

$$r-l\rightarrow-1$$



### 结束条件
这些操作能进行，需要 $k$  大于等于操作数，如果不大于直接退出循环即可。

最后的答案是 $n-(r-l+1)$ 。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi fisrt
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,k,a[N];
void sol(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    ll l=1,r=n,now=0;
    while(l<=r&&k>0){
        if(l==r){
            if(k>=a[l])cout<<n<<endl;
            else cout<<n-1<<endl;
            return ;
        }
        if(now==0){
            if(a[l]<=a[r]){
                if(k<a[l]*2-1)break;
                k-=a[l]*2-1;
                a[r]-=a[l]-1;
                now=1;
                l++;
                continue;
            }
            if(a[l]>a[r]){
                if(k<a[r]*2)break;
                k-=a[r]*2;
                a[l]-=a[r];
                now=0;
                r--;
                continue;
            }

        }
        if(now==1){
            if(a[l]>=a[r]){
                if(k<a[r]*2-1)break;
                k-=a[r]*2-1;
                a[l]-=a[r]-1;
                now=0;
                r--;
                continue;
            }
            if(a[l]<a[r]){
                if(k<a[l]*2)break;
                k-=a[l]*2;
                a[r]-=a[l];
                now=1;
                l++;
                continue;
            }
        }
    }
    cout<<n-(r-l+1)<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();

    return 0;
}
```

---

## 作者：Infinite_Loop (赞：1)

# CF1955C
## 题意
有 $n$ 艘飞船，第 $i$ 艘飞船有一个耐久度 $a_{i}$，现在有 $k$ 次攻击，第一次攻击第一艘飞船，第二次攻击最后一艘飞船，第三次攻击第一艘飞船，以此类推。每次攻击可以让飞船的耐久度下降 $1$，当耐久度为 $0$ 时飞船就会沉没，这时第一艘飞船和最后一艘飞船的位置会改变。当飞船都沉没，将不再攻击。问最终沉没的飞船数为多少。
## 思路
因为 $1 \le k \le 10^{15}$，所以不能使用暴力。我们可以发现以下几个规律：

- 当所有飞船的耐久度总和小于等于 $k$，意味着所有飞船都被击沉，输出 $n$。

- 当耐久度总和大于 $k$，我们可以求出前面被打掉了 $\lceil \frac{k}{2} \rceil$ 的耐久度，后面被打掉了 $\lfloor \frac{k}{2} \rfloor$ 的耐久度。然后从前往后和从后往前各扫一次，求出左右端点，然后就能求出答案了。

需要注意的点：

- 要开 long long。
- 注意向上取整和向下取整。
- 最后输出的是击沉的飞船数，不是还在的飞船数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll t,n,k,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		ll sum=0;
		for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
		if(sum<=k)cout<<n<<endl;
		else{
			sum=0;
			ll l=(k+1)/2,r=k/2,idl=-1,idr=-1;
			for(int i=1;i<=n;i++){
				sum+=a[i];
				if(sum>l){
					idl=i;
					break;
				}
			}
			sum=0;
			for(int i=n;i>=1;i--){
				sum+=a[i];
				if(sum>r){
					idr=i;
					break;
				}
			}
			cout<<n-(idr-idl+1)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

洛谷题目传送门：[CF1955C](https://www.luogu.com.cn/problem/CF1955C)   | |  CF原题传送门：[1955C](https://codeforces.com/contest/1955/problem/C)

#### 简要题意
有 $n$ 只船，每只船都有一个耐久度 $a_i$，它们排成一条队。

进行 $k$ 次操作，每**奇数次**让**队首**的船的耐久度 $-1$，每**偶数次**让**队尾**的船的耐久度 $-1$。当船的耐久度降到 $0$ 时即为沉没，退出队列。

问操作完后有多少只船沉没？
#### 思路
首先，$1\leq k\leq10^{15}$，放弃纯模拟。

可以将 $k$ 次操作分开成前后两次操作 $u, v$，分开操作。

操作途中分两种情况（下面以前面的操作 $u$ 为例）：
* 如果 $a_i \leq u$，说明该船会沉没，$u - a_i$，并将 $a_i$ 标记为 $0$ 后处理下一只船; 
* 如果 $a_i > u$，说明该船不会沉没，且在此操作停止，将 $u$ 清零。 

最后统计标记为 $0$ 的船只数并输出即可。

$AC\space CODE$
---
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    int a;cin>>a; while(a--){
        ll n, k, t=0; cin>>n>>k; ll b[n]; ll u=k/2+k%2, v=k/2;
        for(int i=0; i<n && cin>>b[i]; i++) if(b[i]<=u) u-=b[i],b[i]=0; else b[i]-=u, u=0;
        for(int i=n-1; i>=0; i--) if(b[i]<=v) v-=b[i], b[i]=0 ; else b[i]-=v, v=0;
        for(int i=0; i<n; i++) if(b[i]==0) t++; cout<<t<<endl;
    }
}
```

---

## 作者：ttq012 (赞：0)

首先如果 $\sum\limits_{i=1}^n a_i\le k$ 那么显然 $n$ 个飞船会全部被击落。

否则，显然在前面打了 $\lceil\frac{k}{2}\rceil$ 下，后面打了 $\lfloor\frac{k}{2}\rfloor$ 下。所以直接从前面和后面分别扫一遍求一下答案即可。

时间复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
int a[N], pre[N], suf[N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            pre[i] = pre[i - 1] + a[i];
        for (int i = n; i; i--)
            suf[i] = suf[i + 1] + a[i];
        int presum = (k + 1) / 2, sufsum = k / 2;
        if (accumulate(a + 1, a + n + 1, 0ll) > k) {
            int id, idp;
            for (int i = 1; i <= n; i++) {
                presum -= a[i];
                if (presum < 0) {
                    id = i - 1;
                    break;
                }
            }
            for (int i = n; i; i--) {
                sufsum -= a[i];
                if (sufsum < 0) {
                    idp = n - i;
                    break;
                }
            }
            cout << idp + id << '\n';
        } else cout << n << '\n';
    }
    return 0;
}
```

---

