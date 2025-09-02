# Firefly's Queries

## 题目描述

Firefly is given an array $ a $ of length $ n $ . Let $ c_i $ denote the $ i $ 'th cyclic shift $ ^{\text{∗}} $ of $ a $ . She creates a new array $ b $ such that $ b = c_1 + c_2 + \dots + c_n $ where $ + $ represents concatenation $ ^{\text{†}} $ .

Then, she asks you $ q $ queries. For each query, output the sum of all elements in the subarray of $ b $ that starts from the $ l $ -th element and ends at the $ r $ -th element, inclusive of both ends.

 $ ^{\text{∗}} $ The $ x $ -th ( $ 1 \leq x \leq n $ ) cyclic shift of the array $ a $ is $ a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1} $ . Note that the $ 1 $ -st shift is the initial $ a $ .

 $ ^{\text{†}} $ The concatenation of two arrays $ p $ and $ q $ of length $ n $ (in other words, $ p + q $ ) is $ p_1, p_2, ..., p_n, q_1, q_2, ..., q_n $ .

## 说明/提示

For the first test case, $ b = [1, 2, 3, 2, 3, 1, 3, 1, 2] $ .

## 样例 #1

### 输入

```
5
3 3
1 2 3
1 9
3 5
8 8
5 5
4 8 3 2 4
1 14
3 7
7 10
2 11
1 25
1 1
6
1 1
5 7
3 1 6 10 4
3 21
6 17
2 2
1 5
1 14
9 15
12 13
5 3
4 9 10 10 1
20 25
3 11
20 22```

### 输出

```
18
8
1
55
20
13
41
105
6
96
62
1
24
71
31
14
44
65
15```

# 题解

## 作者：Super_Cube (赞：3)

# Solution

由于 $c$ 中每 $n$ 个数的总和固定，对其进行分块，块长为 $n$。对于 $l,r$ 算出其所在块，中间整块的和可直接算，左右两边的散块是 $a$ 的前后缀，预处理其前后缀和即可。

# Code

```cpp
#include<bits/stdc++.h>
long long a[400005];
int T,n,m;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]),a[n+i]=a[i];
		for(int i=1;i<=(n<<1);++i)a[i]+=a[i-1];
		for(long long l,r;m--;){
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",(r/n-(l-1)/n-1)*a[n]+a[(l-1)/n%n+n]-a[(l-1)/n%n+(l-1)%n]+a[r/n%n+r%n]-a[r/n%n]);
		}
	}
	return 0;
}

```

---

## 作者：Phigros_11calors (赞：2)

### 题意
给你一个长度为 $n$ 的序列 $a$，将 $i \in (1,n)$ 开始的 $a$ 的循环序列（指把 $a$ 的两部分 $a_{(i,n)}$ 和 $a_{(1,i-1)}$ 按照前者在前，后者在后的顺序重新拼接起来形成的序列）拼接到 $b$ 的后面，得到长度为 $n^2$ 的序列 $b$。

例如，序列 $a$ 为 $[1,2,3]$ 时，序列 $b$ 为 $[1,2,3,2,3,1,3,1,2]$。
### 思路
由于是循环序列，我们可以把 $n^2$ 压缩为 $2n-1$，例如当 $a$ 为 $[1,1,4,5,1,4]$ 时，我们就可以把 $b$ 视为 $[1,1,4,5,1,4,1,1,4,5,1]$，然后预处理前缀和，对于每一次询问，计算 $l,r$ 在前缀和数组中的偏移量，然后计算结果，输出即可。由于 $a_i$ 最大可达 ${10}^6$，而数组 $b$ 的长度最大可达 $4 \times {10}^{10}$，两者相乘可达 $4 \times {10}^{16}$，所以要开 `long long`。

时间复杂度 $O(\sum_{i=1}^{t} n_i+q_i)$。
### AC代码

```cpp
//CF2009F
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
typedef long long ll;
const int N=2e5+5;
ll v[2*N];
ll presum[2*N];
int n,q;
inline void Solve(){
	ll l,r;
	cin>>l>>r;
	l--;
	ll ful=(r/n)-(l/n)-1;
	ll result=ful*presum[n];
	ll loffset=(l/n)%n;
	ll roffset=(r/n)%n;
	result+=(presum[loffset+n]-presum[loffset+l%n]);
	result+=(presum[roffset+r%n]-presum[roffset]);
	
	printf("%lld\n",result);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(register int i=1;i<=n;i++){
			cin>>v[i];
			v[i+n]=v[i];
		}
		int mn=2*n;
		for(register int i=1;i<=mn;i++){
			presum[i]=presum[i-1]+v[i];
		}
		while(q--){
			Solve();
		}
	}
}

```
[AC 记录](https://codeforces.com/contest/2009/submission/295867469)

---

## 作者：_H17_ (赞：1)

## 题目分析

考虑到把序列按照排列的方法分成 $n$ 个块，分别表示 $a$ 偏移到 $1\sim n$ 之后的序列。

注意到每个块的值相同，都是 $1\sim n$，然后处理零散块。

零散块考虑前缀和，由于偏移有类似于环的性质，考虑破环成链。

查询 $(l,r)$ 正常用前缀和是 $s_r-s_{l-1}$，此时是偏移到 $1$，考虑扩展到偏移为 $x$，那么前缀和就变成 $s_{r+x-1}-s_{l+x-2}$。

时间复杂度 $O(T\times(n+q))$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=2e5+1;
int T,n,q,a[N],s[N<<1],sum;
int query(int x,int l,int r){//偏移到x之后查询l,r(l,r属于[1,n])
    //x~n+x-1
    return s[x+r-1]-s[x+l-2];
}
int get_block(int x){
    return (x-1)/n+1;
}//获得块的编号
void Main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }//前缀和
    for(int i=1;i<=n;i++)
        s[n+i]=a[i]+s[n+i-1];//破环成链
    sum=s[n];//求出和
    for(int l,r;q;--q){
        cin>>l>>r;
        if(get_block(l)==get_block(r))
            cout<<query(get_block(l),l-(get_block(l)-1)*n,r-(get_block(r)-1)*n)<<'\n';//只有零散块
        else{
            int ret=0;
            ret+=query(get_block(l),l-(get_block(l)-1)*n,n)+query(get_block(r),1,r-(get_block(r)-1)*n);//两个零散块
//            cerr<<ret<<'\n';
            ret+=(get_block(r)-get_block(l)-1)*sum;//整块
            cout<<ret<<'\n';
        }
    }
    return;
}
signed main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

---

