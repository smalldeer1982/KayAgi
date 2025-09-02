# 题目信息

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

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

Firefly 被给定一个长度为 $n$ 的数组 $a$。设 $c_i$ 表示 $a$ 的第 $i$ 个循环移位 $^{\text{∗}}$。她创建了一个新数组 $b$，使得 $b = c_1 + c_2 + \dots + c_n$，其中 $+$ 表示数组的拼接 $^{\text{†}}$。

然后，她向你提出 $q$ 个查询。对于每个查询，输出 $b$ 数组中从第 $l$ 个元素到第 $r$ 个元素（包括两端）的子数组中所有元素的和。

$^{\text{∗}}$ 数组 $a$ 的第 $x$ 个（$1 \leq x \leq n$）循环移位是 $a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1}$。注意，第 $1$ 个移位是初始的 $a$。

$^{\text{†}}$ 两个数组 $p$ 和 $q$ 的拼接（即 $p + q$）是 $p_1, p_2, ..., p_n, q_1, q_2, ..., q_n$。

#### 说明/提示

对于第一个测试用例，$b = [1, 2, 3, 2, 3, 1, 3, 1, 2]$。

### 题解分析与结论

#### 题解思路对比

1. **Super_Cube 的题解**：
   - **思路**：将 $b$ 数组分为长度为 $n$ 的块，每个块的和是固定的。通过预处理前缀和，计算查询区间内的整块和散块的和。
   - **难点**：处理查询区间跨越多个块的情况，计算散块的和。
   - **优化**：通过预处理前缀和，减少计算量，时间复杂度为 $O(T \times (n + q))$。

2. **Phigros_11calors 的题解**：
   - **思路**：将 $b$ 数组压缩为 $2n-1$ 的长度，预处理前缀和，计算查询区间内的和。
   - **难点**：处理查询区间在压缩后的数组中的偏移量。
   - **优化**：通过压缩数组和预处理前缀和，减少计算量，时间复杂度为 $O(T \times (n + q))$。

3. **_H17_ 的题解**：
   - **思路**：将 $b$ 数组分为 $n$ 个块，每个块的值相同，处理零散块时使用前缀和。
   - **难点**：处理查询区间跨越多个块的情况，计算零散块的和。
   - **优化**：通过破环成链和预处理前缀和，减少计算量，时间复杂度为 $O(T \times (n + q))$。

#### 最优思路与技巧

- **关键思路**：将 $b$ 数组分为长度为 $n$ 的块，每个块的和是固定的。通过预处理前缀和，计算查询区间内的整块和散块的和。
- **技巧**：使用破环成链的方法，将循环数组转化为线性数组，方便计算前缀和。
- **优化**：通过预处理前缀和，减少查询时的计算量，时间复杂度为 $O(T \times (n + q))$。

#### 可拓展之处

- **同类型题**：处理循环数组的查询问题，可以通过分块和预处理前缀和的方法优化计算。
- **类似算法套路**：在处理大规模数组查询时，可以通过分块、预处理前缀和、压缩数组等方法优化计算。

#### 推荐题目

1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

### 所选高星题解

#### Super_Cube 的题解（4星）

- **关键亮点**：通过分块和预处理前缀和，高效处理查询区间内的整块和散块的和。
- **代码实现**：

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

#### Phigros_11calors 的题解（4星）

- **关键亮点**：通过压缩数组和预处理前缀和，高效处理查询区间内的和。
- **代码实现**：

```cpp
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

#### _H17_ 的题解（4星）

- **关键亮点**：通过破环成链和预处理前缀和，高效处理查询区间内的整块和散块的和。
- **代码实现**：

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

### 总结

通过分块、预处理前缀和、破环成链等方法，可以高效处理循环数组的查询问题。推荐使用 Super_Cube 的题解，思路清晰，代码简洁，易于理解。

---
处理用时：65.16秒