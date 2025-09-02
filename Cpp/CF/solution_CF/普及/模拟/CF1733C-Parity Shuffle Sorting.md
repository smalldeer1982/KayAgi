# Parity Shuffle Sorting

## 题目描述

You are given an array $ a $ with $ n $ non-negative integers. You can apply the following operation on it.

- Choose two indices $ l $ and $ r $ ( $ 1 \le l < r \le n $ ).
- If $ a_l + a_r $ is odd, do $ a_r := a_l $ . If $ a_l + a_r $ is even, do $ a_l := a_r $ .

Find any sequence of at most $ n $ operations that makes $ a $ non-decreasing. It can be proven that it is always possible. Note that you do not have to minimize the number of operations.

An array $ a_1, a_2, \ldots, a_n $ is non-decreasing if and only if $ a_1 \le a_2 \le \ldots \le a_n $ .

## 说明/提示

In the second test case, $ a $ changes like this:

- Select indices $ 3 $ and $ 4 $ . $ a_3 + a_4 = 3 $ is odd, so do $ a_4 := a_3 $ . $ a = [1, 1000000000, 3, 3, 5] $ now.
- Select indices $ 1 $ and $ 2 $ . $ a_1 + a_2 = 1000000001 $ is odd, so do $ a_2 := a_1 $ . $ a = [1, 1, 3, 3, 5] $ now, and it is non-decreasing.

In the first and third test cases, $ a $ is already non-decreasing.

## 样例 #1

### 输入

```
3
2
7 8
5
1 1000000000 3 0 5
1
0```

### 输出

```
0
2
3 4
1 2
0```

# 题解

## 作者：winter2020 (赞：11)

upd：修改一处笔误

题目大意略，[题目传送门](https://www.luogu.com.cn/problem/CF1733C)

不妨从两个极端（开头和末尾）开始考虑。

先对 $a_1$ 和 $a_n$ 进行一遍操作，让两数变相同，记该数为 $c$。

对于其他数进行一次遍历，分类讨论 $a_i+c$：

- 如果 $a_i+c$ 是奇数：$l=1$，$r=i$ 即可满足要求。

- 如果 $a_i+c$ 是偶数：$l=i$，$r=n$ 即可满足要求。

操作方案总数显然为 $n-1$，注意特判 $n=1$ 的情况即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n;
int a[N], ansa[N], ansb[N], res;

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	if (n == 1) {
	    puts("0");
	    return;
	}
    cout << n - 1 << endl;
    cout << 1 << " " << n << endl;
    int c = (a[1] + a[n]) % 2? a[1] : a[n];
    for (int i = 2; i < n; i ++ )
        if (c + a[i] & 1) cout << 1 << " " << i << endl;
        else cout << i << " " << n << endl;
    return;
}


int main() {
	int T;
	cin >> T;
	while (T -- ) 
		solve();
	return 0;
}
```

---

## 作者：shitingjia (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1733C)

### 题目思路

构造题目嘛，怎么简单怎么造。

单调不减？好吧，干脆全部相等好了。

从哪里开始呢？就从最极端的 $a_1$ 和 $a_n$ 开始，先把这两个数统一，之后的数都和他们一样。具体按照题意来做即可，注意**赋值的方向**。

接下来枚举剩下的数，当 $a_i + a_1$ 为奇数时（加 $a_1$ 还是 $a_n$ 没有区别，因为两数值相等），需要 $a_i$ 左边的数给它赋值，即 $a_1$。反之，就用 $a_n$ 给它赋值。

操作次数一共是 $n-1$。记得是在每组数据的最前面输出。

更多细节请见代码。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,a[N]; 
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		cout<<n-1<<endl;
		if(n!=1){//n=1的话不需要做此操作，直接输出0 
			cout<<1<<" "<<n<<endl;
			int sum=a[1]+a[n];
			if(sum&1)	a[n]=a[1];
			else	a[1]=a[n];
		}
		for(int i=2;i<n;i++){//枚举剩下的数字 
			int sum=a[i]+a[n];
			if(sum&1){//这里相当于a[i]=a[1];
				cout<<1<<" "<<i<<endl;
			}
			else{//这里相当于a[i]=a[n];
				cout<<i<<" "<<n<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：taojinchen (赞：2)

# 思路
因为 $a_1 \le a_2 \le \dots \le a_n$，所以有一种方法是把全部的数都统一。

第一步，统一两边。只要对两个端点的数进行一次操作就可以统一两边。

第二步，统一中间。中间的数 $a_i$ 加 $a_1$ 是奇数就用第一个数统一中间的数，否则就用最后一个数统一中间的数。

注意特判数列中只有一个元素的情况，可以直接不用操作。
# code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int kM=2e5+5;
ll n,x,y,i,q,cnt,cc,c,a[kM];
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>q;//多测
  while(q--){
    cin>>n;//输入序列长度
    for(i=1;i<=n;i++){
      cin>>a[i];//输入序列
    }
    cout<<n-1<<"\n";
    if(n!=1){//统一两边
      cout<<1<<" "<<n<<"\n";
      if((a[1]+a[n])&1)a[n]=a[1];
      else a[1]=a[n];
    }
    for(i=2;i<n;i++){//统一中间
      if((a[i]+a[n])&1)cout<<1<<" "<<i<<"\n";
      else cout<<i<<" "<<n<<"\n";
    }
  }
  return 0;
}
```

---

## 作者：wawatime1 (赞：1)

### 题目分析
- 首先观察操作规则，当 $a_l + a_r$ 为奇数时，$a_r := a_l$；当为偶数时，$a_l := a_r$。

- 我们可以利用这个操作来逐步调整数组元素的顺序。对于一个数组，我们可以从左到右扫描，尝试将较小的元素移动到左边，较大的元素移动到右边。

- 考虑以下策略：我们可以先找到数组中的最小元素，通过操作将其移动到数组的第一个位置，然后在剩余的子数组中找到最小元素，将其移动到第二个位置，以此类推。

- 具体实现时，我们可以使用两层循环。外层循环控制要放置的位置，内层循环用于寻找合适的元素并进行操作。

---

## 作者：technopolis_2085 (赞：1)

有点意思的构造题。

我们可以先将每一个数的奇偶性质拆出来，然后拆成“一个奇数加若干个偶数”或者“一个偶数加上若干个奇数”的连续段。具体拆法根据第一个数的奇偶性决定。若第一个数是奇数，则用第一种拆法，否则用第二种拆法。

这样做的意义在于：每一个连续段的第一个元素的奇偶性和后面的都不同，使得第一个元素和后面任意一个元素相加总为奇数，所以这样就可以对连续段的第一个元素和后面的每一个元素进行一次操作，将后面的数赋值为前面的数。这样可以把整个连续段都赋值成一个数。

举一个例子：

假设连续段为 $[3,2,4]$，这个连续段满足第一个数和后面的数的奇偶性都不同。

然后我们选择 $l=1,r=2$。此时 $a_1+a_2$ 为奇数，所以将 $a_2$ 赋值为 $a_1$，序列变成 $[3,3,4]$。然后选择 $l=1,r=3$，此时 $a_1+a_3$ 为奇数，将 $a_3$ 赋值为 $a_1$，此时序列变成 $[3,3,3]$。

然后我们发现每一个连续段都可以变成第一个元素。所以目标就变成了将每一个连续段的第一个元素变成不降的。

由于每一个连续段的第一个元素的奇偶性都是相同的，所以每一次可以把后面的连续段的第一个元素赋值到前面的连续段的第一个连续元素。

还是举个例子：

假设序列变成了 $[3,...],[5,...],[1,...]$，现在 第二个连续段的第一个元素加上第三个连续段的第一个元素是偶数，即 $5+1=6$，此时可以将 $5$ 赋值成 $1$，同理，也可以将 $3$ 赋值成 $1$，因为 $3+1=4$，是偶数。

这样，整个序列就是不降序了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int a[maxn];
struct kuai{
	int l,r;
};

kuai b[maxn];

int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		int n;
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		int tot=0;
		int op=a[1]%2;//每一个连续段的第一个元素的奇偶性
		int lst=1;
		for (int i=2;i<=n;i++){
			if (a[i]%2==op){
				tot++;
				b[tot].l=lst;
				b[tot].r=i-1;
				lst=i;
			}
		}
		
		tot++;//[lst,n]还是一个连续段
		b[tot].l=lst;
		b[tot].r=n;
		vector<pair<int,int> > ans;
		ans.clear();
		for (int i=tot-1;i>=1;i--) ans.push_back(make_pair(b[i].l,b[i+1].l));//将每个连续段的第一个元素变成不降顺序
		for (int i=1;i<=tot;i++){
			int j=b[i].l+1;
			while (j<=b[i].r){//将每一个连续段的其他元素赋值成第一个元素
				ans.push_back(make_pair(b[i].l,j));
				j++;
			}
		}
		
		printf("%d\n",(int)ans.size());
		for (int i=0;i<(int)ans.size();i++) printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
} 
```


---

## 作者：rqzhangzehao (赞：0)

## 一：题目思路

看完题目，发现是只需找出一种方案，所以**数组单调不减**可以理解成**数组元素全部相等**。

于是，我们不妨让 $a[1]=a[n]$，然后，我们就枚举数组中第 $2 \sim n-1$ 个元素，当 $a[1]+a[i]$ 为奇数时，就让 $a[i]=a[1]$，否则就让 $a[i]=a[r]$，循环结束后就可以让数组中的所有元素都相等。

注：当 $n=1$ 时特判输出 $0$。

## 二：AC 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		if(n==1){
			cout<<0<<"\n";
		}
		else{
			cout<<n-1<<"\n";
			cout<<1<<" "<<n<<"\n";
			if((a[1]+a[n])%2==0)a[1]=a[n];
			else a[n]=a[1];
			for(int i=2;i<n;i++){
				if((a[i]+a[n])%2==0){
					cout<<i<<" "<<n<<"\n";
				}
				else{
					cout<<1<<" "<<i<<"\n";
				}
			}
		}
	}
}
```

---

## 作者：LZYAC (赞：0)

## 思路

考虑到它给的两个操作都是将一个元素赋值给另一个元素。那么我们考虑让他们全部相等。

那么就只用让第一个和最后一个相等，中间的如果是奇数，那么将把 $a_r$ 赋值给 $a_i$ 那么这里的 $r$ 就是 $n$。否则的话就是把 $a_l$ 赋值给 $a_i$ 那么这里的 $l$ 就是 $1$。

注意刚刚的情况至少有两个元素。对于只有一个元素的我们就特判一下。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[100010];
void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	if(n==1){
		printf("0\n");
		return ;
	}
	printf("%lld\n",n-1);
	printf("1 %lld\n",n);
	if((a[1]+a[n])%2==0) a[1]=a[n];
	else a[n]=a[1];
	for(int i=2;i<n;i++){
		if((a[1]+a[i])%2==0) printf("%lld %lld\n",i,n);
		else printf("1 %lld\n",i);
	}
}
signed main(){
	scanf("%lld",&t);
	while(t--) solve();
    return 0;
}

```

---

