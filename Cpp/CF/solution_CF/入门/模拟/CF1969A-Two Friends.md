# Two Friends

## 题目描述

Monocarp 想要举办一个聚会。他有 $n$ 个朋友，并且他想要让他们之中的至少 $2$ 人来参加聚会。

第 $i$ 个朋友的最好的朋友是 $p_i$。每一个 $p_i$ 都是不一样的，并且对于所有的 $i \in [1, n]$，$p_i \neq i$。

Monocarp 可以给朋友们发送邀请。如果第 $i$ 个朋友和第 $p_i$ 个朋友都收到了邀请（注意第 $p_i$ 个朋友不一定真的要去参加聚会），那么第 $i$ 个朋友会去参加聚会。每份邀请都会发送给其中一位朋友。

举个例子，如果 $p = [3,1,2,5,4]$，并且 Monocarp 给朋友 $[1, 2, 4, 5]$ 发邀请，那么朋友 $[2, 4,5]$ 会去参加聚会。朋友 $1$ 不会去参加聚会因为他最好的朋友没有收到邀请；朋友 $3$ 不会去参加聚会因为他没有受到邀请。

求 Monocarp 最少需要发出的邀请数以让至少 $2$ 个朋友来参加聚会。

## 样例 #1

### 输入

```
3
5
3 1 2 5 4
4
2 3 4 1
2
2 1```

### 输出

```
2
3
2```

# 题解

## 作者：__bjxx0201__ (赞：3)

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1969A)

题目让我们求出如果要邀请到 $2$ 个人，需要多少次邀请。如果我们要邀请一个朋友来，就要邀请这个朋友的朋友，如果要邀请这个朋友的朋友，就要邀请这个朋友的朋友的朋友。但是如果这个朋友的朋友是自己，就直接输出 $2$，否则输出 $3$。

代码：

```
#include <bits/stdc++.h>
using namespace std;
int t;
int main() {
    cin>>t;
    while (t--) {
    	int n,a[1000001];
    	bool p=false;
    	cin>>n;
    	for (int i=1;i<=n;i++) cin>>a[i];
    	for (int i=1;i<=n;i++) {
    		if (i==a[a[i]]) {
    			cout<<"2\n";
    			p=true;
    			break;
			}
		}
		if (!p) cout<<"3\n";
	}
    return 0;
}
```

---

## 作者：__Floze3__ (赞：1)

## 思路简介

仔细一想发现，我们至多只需要发送 $3$ 份邀请函就能至少邀请来 $2$ 个人，只要邀请一个人，他的最好的朋友，以及这个最好的朋友的最好的朋友即可。同时，如果有 $2$ 个人互为最好的朋友，我们只需要发出 $2$ 份邀请函。那么对这种情况进行判断即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int T, n, a[N];

int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        int ans = 3;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) {
            if (a[a[i]] == i) ans = 2;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：LJMljm (赞：0)

### 题目解释
根据题目介绍得知，$t$ 组数据，每次至少寻找一个组合，且为 $2$ 人以上。所以需发邀请函数只有 $2$ 种情况，分别是发 $1$ 或 $2$ 张。最后再判断有没有不满足情况就行了。
### 代码如下↓
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[55] , t, n;
int main(){
    cin>> t;
    for(int i = 1; i <= t; i++)
    {
    	cin>> n;
    	int ans = 0;
    	for(int j = 1; j <= n; j++)
    		cin>> p[j];
		int k = 0;
    	for(int j = 1; j <= n; j++)
    	{
    		k= (j == p[ p[j] ]);
    		if(k) break;
    	}
		cout<< 3- k << endl;
    }
    return 0;
}
```

---

## 作者：The_FAKIR (赞：0)

## CF1969A Two Friends 题解

#### [题目传送门](https://www.luogu.com.cn/problem/CF1969A)

### 题意
一个人有 $n$ 朋友。

如果第 $i$ 个朋友和 $p_i$ 个朋友都收到了邀请，注意第 $p_i$ 个朋友不一定真的要去参加聚会，那么第 $i$ 个朋友会去参加聚会。每份邀请都会发送给其中一位朋友。

### 思路

题目中说了：只给少于 $3$ 个朋友发邀请函还至少有 $2$ 个朋友来参加聚会是不可能的。

所以要邀请一个人至少要邀请三个人。

但如果是他的编号也是他的朋友的朋友的编号（也就是说他的朋友的朋友是他自己），那么就只要两次邀请。


注意有多组数据。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100010;
int a[maxn],b[maxn];
int T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
	    for(int i=1;i<=n;i++){
	    	if(i==a[a[i]]){
	    		cout<<2<<'\n';
				goto brk;//跳转到第二十行 
			}
	    }
	    cout<<3<<'\n';
		brk:;
	}
	return 0;
} 
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/CF1969A)
## 分析
很明显，如果 $i$ 个人会去参加，那么 Monocarp 必须得邀请 $p_i$，而此时 Monocarp 只需要再邀请 $p_{p_i}$，那么 $p_i$ 就会参加，这样就已经有 $2$ 个人参加派对了，故只需要邀请 $3$ 个人。需要额外注意的是，如果 $i$ 与 $p_{p_i}$ 相等的话，只需要邀请 $2$ 个人就行了（$i$ 与 $p_i$）。
## Code
```cpp
#include<iostream>
using namespace std;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int t,n,p[51];
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1;i<=n;++i) cin>>p[i];
		bool flag=false;//初始要赋值为false
		for(int i=1;i<=n;++i)
			if(i==p[p[i]]) {//判断i与p[p[i]]是否相等
				flag=true;
				break;//如果已经找到了就退出
			}
		cout<<(flag?2:1)<<"\n";//如果i与p[p[i]]相等输出2，反之输出3
	}
	return 0;
}
```

---

## 作者：SB_ME (赞：0)

~~本蒟蒻第一次写题解~~

[题目传送门](https://www.luogu.com.cn/problem/CF1969A)
### 题目分析
其实就是寻找一个最少次寻找的一个组合，但是要 $2$ 人以上，这样的话邀请人数就最多就只有 $3$ 种，（也就是朋友的朋友的朋友）再判断一下是否会出现不满足的情况即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100],b[100];
int main(){
	int n,m;
	cin>>n;
	while(n--)
	{
		int ans=0;
		cin>>m;
		  for(int i=1;i<=m;i++)
			cin>>a[i];
		int j=3,k=0;
	          for(int i=1;i<=m;i++)
         	       if(i==a[a[i]]) {
            	           k=1;
                           break;
                       }
                 ans=j-k;
                 cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：Furina_Saikou (赞：0)

这道题还是要点思考的。

# 思路

依题意可知如果要邀请 $i$，那就要邀请 $p_i$，这样就能保证 $i$ 参加，同理要再保证 $p_i$ 参加就把 $p_{p_i}$ 给邀请了，然后就能保证两人参与。特别需要考虑 $p_i$ 是否等于 $i$，这样只要将这两人邀请就能让他们都参加。

所以我们只要判断是否出现 $i = p_i$ 的特殊情况，出现了就输出 $2$，否则输出 $3$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1145;
int t,n,a[N];
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        bool flag=0;
        for(int i=1;i<=n;i++)//寻找互为最好朋友的情况
        {
            if(a[a[i]]==i)//判断两人是否互为最好朋友
            {
                flag=1;
                break;
            }
        }
        if(flag)
        {
            cout<<"2\n";
        }else
        {
            cout<<"3\n";
        }
    }
}
```

---

## 作者：lpx666666 (赞：0)

## 题面
一个人有 $n$ 个朋友，每个朋友有另一个好朋友，需要邀请他的另一个朋友他才会来，只要邀请了即可，求邀请两个人至少要几次邀请。
## 思路
可以邀请一个人，再邀请他的朋友，再邀请他朋友的朋友，这样就只要三次，但如果他朋友的朋友就是自己，那就只需要两次，所以只需判断有没有这种双向的就行。
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int t,arr[101];
int main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
		}
		int o=0;
		for(int i=1;i<=n;i++){
			if(arr[arr[i]]==i){
				o=1;
			}
		}
		if(o){
			cout<<2<<endl;
		}
		else{
			cout<<3<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Laisira (赞：0)

### 题面
$t$ 组数据，每次给定长为 $n$ 的序列 $p$，指 $i$ 的朋友 $p_i$，当 $i$ 和 $p_i$ 都收到邀请时 $i$ 会去，求让 $2$ 个及以上人取得最少邀请数。

### 思路
我们钦定 $i$ 一定要去，就要邀请 $p_i$，然后我们只需要邀请一下 $p_{p_i}$，$p_i$ 就会去了，可以证明这是最少的。特殊的，当 $p_{p_i}=i$ 时只需要邀请 $2$ 次。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[5005];
int main()
{
    int t,n;
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>p[i];
        int opt=0;
        for(int i=1;i<=n;i++)
            if(i == p[p[i]]) {
                opt=1;
                break;
            }
        cout<<3-opt<<"\n";
    }
}
```

---

