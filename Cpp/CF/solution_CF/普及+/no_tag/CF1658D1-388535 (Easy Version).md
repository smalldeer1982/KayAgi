# 388535 (Easy Version)

## 题目描述

This is the easy version of the problem. The difference in the constraints between both versions is colored below in red. You can make hacks only if all versions of the problem are solved.

Marin and Gojou are playing hide-and-seek with an array.

Gojou initially performs the following steps:

- First, Gojou chooses $ 2 $ integers $ l $ and $ r $ such that $ l \leq r $ .
- Then, Gojou makes an array $ a $ of length $ r-l+1 $ which is a permutation of the array $ [l,l+1,\ldots,r] $ .
- Finally, Gojou chooses a secret integer $ x $ and sets $ a_i $ to $ a_i \oplus x $ for all $ i $ (where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

Marin is then given the values of $ l,r $ and the final array $ a $ . She needs to find the secret integer $ x $ to win. Can you help her?

Note that there may be multiple possible $ x $ that Gojou could have chosen. Marin can find any possible $ x $ that could have resulted in the final value of $ a $ .

## 说明/提示

In the first test case, the original array is $ [3, 2, 1, 0] $ .

In the second test case, the original array is $ [0, 3, 2, 1] $ .

In the third test case, the original array is $ [2, 1, 0] $ .

## 样例 #1

### 输入

```
3
0 3
3 2 1 0
0 3
4 7 6 5
0 2
1 2 3```

### 输出

```
0
4
3```

# 题解

## 作者：sprads (赞：6)

**题目链接**：[CF1658D1](https://codeforces.com/contest/1658/problem/D1)

两种做法。

### 第一种做法

考虑异或上 $1$ 的性质：把 $1$ 变成 $0$，把 $0$ 变成 $1$。那么就对**二进制下**的**每一位**进行考虑。

对于**每一个**二进制位，统计排列中当前位上为 $1$ 的个数，$a_i$ 当前位上为 $1$ 的个数。

如果统计得到的个数不相同，就意味着需要把 $1$ 变 $0$，$0$ 变 $1$ 来改变 $1$ 的个数。也就是说，异或的数 $x$ 的当前二进制位为 $1$。考虑完每一位后就得到了 $x$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = (1 << 17) + 5;
int T,L,R,a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&L,&R);
		for(int i = L;i <= R;i++)
			scanf("%d",&a[i]);
		int res = 0;//res 就是 x
		for(int j = 0;j <= 17;j++){
			int c1 = 0,c2 = 0;
			for(int i = L;i <= R;i++){
				if(i & (1 << j))c1++;
				if(a[i] & (1 << j))c2++;//分别统计
			}
			if(c1 != c2)
				res += 1 << j;//x当前位置为1
		}
		printf("%d\n",res);
	}
	return 0;
}
```

### 第二种做法

考虑到排列中一个非常特殊的数 $0$。$0$ 异或上任何数 $v$，结果都等于 $v$。那就枚举所有 $a_i$，认为它就是 $x$，对应排列中的 $0$。

判断 $a_i$ 是否为 $x$：显然所有 $a_i$ 的值不相同，异或 $x$ 还原为排列也不可能相同。判断是否能还原成排列只需判断上界和下界即可。又显然下界一定大于等于 $0$，那么只需要看上界，找到 $a_i$ 异或上其它 $a$ 值后的最大值来判断。

此时，转化为最大异或和问题，用 trie 维护即可。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = (1 << 17) + 5;
int T,L,R,a[N];
int cnt,ch[20*N][2];
void insert(int v){//插入数值v
	int p = 0;
	for(int i = 17;i >= 0;i--){
		int x = (v >> i) & 1;
		if(!ch[p][x])
			ch[p][x] = ++cnt;
		p = ch[p][x];
	}
}
int query(int v){//查找异或v能得到的最大值
	int p = 0,res = 0;
	for(int i = 17;i >= 0;i--){
		int x = (v >> i) & 1;
		if(ch[p][x ^ 1]){
			res += 1 << i;
			p = ch[p][x ^ 1];
		}
		else p = ch[p][x];
	}
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&L,&R);
		for(int i = 0;i <= cnt;i++)
			ch[i][0] = ch[i][1] = 0;
		cnt = 0;
		for(int i = L;i <= R;i++){
			scanf("%d",&a[i]);
			insert(a[i]);
		}
		for(int i = L;i <= R;i++){
			if(query(a[i]) > R)continue;//上界大于R，当前ai不能是x
			printf("%d\n",a[i]);
			break;
		}
	}
	return 0;
}
```


---

## 作者：JS_TZ_ZHR (赞：3)

## 题意：

给定 $l,r$ 和一个长为 $r-l+1$ 的所有数都不相等的序列 $a$。请你找到任意一个数 $x$ 满足序列 $a$ 中的所有数异或上 $x$ 后正好为 $[l,l+1,...,r-1,r]$ 的一个排列

## 题解：

显然 $a$ 中一定存在一个数 $a_i$ 使得 $a_i$ 异或 $x$ 等于 $l$。所以我们可以确定存在一个 $a_i$ 使得 $x=a_i\oplus l$，这里 $\oplus$ 指异或。

又由于 $a$ 中的数互不相同，所以其中的数异或上 $x$ 也互不相同。故当 $a$ 中的数异或上 $x$ 后最大值为 $r$，最小值为 $l$ 时，就可以确定此时 $a$ 取到了 $[l,r]$ 中间的每个值。 这个用 trie 维护即可。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int T,l,r,a[N],cnt,trie[N][30],b[N];
void insert(int sum){
	int now=0;
	for(int i=17;i>=0;i--){
		bool tmp=(1<<i)&sum;
		if(!trie[now][tmp])trie[now][tmp]=++cnt;
		now=trie[now][tmp];
	}
}
int Max(int sum){
	int now=0,res=0;
	for(int i=17;i>=0;i--){
		bool tmp=(1<<i)&sum;
		if(!trie[now][tmp^1])now=trie[now][tmp];
		else now=trie[now][tmp^1],res+=(1<<i);
	}
	return res;
}
int Min(int sum){
	int now=0,res=0;
	for(int i=17;i>=0;i--){
		bool tmp=(1<<i)&sum;
		if(!trie[now][tmp])now=trie[now][tmp^1],res+=(1<<i);
		else now=trie[now][tmp];
	}
	return res;
}
signed main() {
	cin>>T;
	while(T--){
		cin>>l>>r;
		for(int i=0;i<=cnt;i++)trie[i][0]=trie[i][1]=0;
		cnt=0;
		for(int i=l;i<=r;i++)cin>>a[i],b[i]=a[i]^l;
		for(int i=l;i<=r;i++)insert(a[i]);
		for(int i=l;i<=r;i++){
			if(Max(b[i])==r&&Min(b[i])==l){
				cout<<b[i]<<endl;
				break;
			}
		}
	}
}
```


---

## 作者：SnowTrace (赞：1)

赛场上看到这题，把我给卡住了。


~~（翻了一遍提交记录，我的方法似乎是独家的）~~

# 思路：

因为异或是一种二进制运算，

所以不妨考虑先将所有的数字都转成二进制。

然后再仔细想一下，

你就会发现 既然这个全排列是和同一个数进行异或运算，

所以我们可以直接按位考虑。

举个例子：

比如说这个要求的数转成二进制时第一位是一，

那么，对于和这个数进行异或的数（也就是那个全排列），

不管前面几位怎么样变换，

第一位为零时 都会在最终结果处产生一个一；

第一位为一时 都会在最终结果处产生一个零。

也就是说，只需要针对所有的这些数中每一位一的个数和零的个数进行考虑。

由此我们可以想到桶排序。

记录这个全排列中所有的数转成二进制以后 ，

对于每一位数 都加进这一位数所对应的桶计数数组里。

比如说某数转为二进制后第三位为一 那桶数组的第三项就要加上一，

对于异或的结果 我们也这样处理。

分别存在两个不同的桶数组中，

随后我们遍历两个桶数组，

对于两个桶数组的某项，

如果它们相等 那就说明要求的数化成2进制时的关于这一项的位为零。

因为桶计数实际上统计的是一的个数，

如果它们不相等 那就说明要求的数化成二进制是关于这一项的位为一。

（因为题目中写到保证有解 那么就可以省去判断这一步骤）

实测能过。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int __pow(int h){//计算2的次幂
	int p =1;
	for(int i =0;i<h;i++)p*=2;
	return p;
}
int main(){
	int t;
	cin >> t;
	while(t--){
		int l,r;
		cin >> l >> r;
		int ans =0;
		int tong1[30] = {0};
		int tong2[30] = {0};
		for(int i =l;i<=r;i++){
			int qaq;
			cin >> qaq;
			int j =0;
			int num =i;
			int k =0 ;
			while(num !=0){
				tong2[k]+=num%2;
				num/=2;
				k++;
			}//全排列转二进制
			while(qaq!=0){
				tong1[j]+=qaq%2;
				qaq/=2;
				j++;
			}//异或后的全排列转二进制
		}for(int i =0;i<=24;i++){
			//cout << tong1[i];
			if(tong1[i] != tong2[i]){
				ans+=__pow(i); 
			}//遍历桶数组并算出答案
		}
	cout << ans << endl;}
	}
```



---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1658d1-388535-easy-version-de-ti-jie/)
## 题目大意
给定 $l,r$ 和一个长为 $r−l+1$ 的所有数都不相等的序列 $a$。请你找到任意一个数 $x$ 满足序列 $a$ 中的所有数异或上 $x$ 后正好为 $[l,l+1,\cdots,r−1,r]$ 的一个排列。

- $t$ 组数据，$1\leqslant t\leqslant 10^5$。
- $\color{red}{0=l}\color{black}\leqslant r,a_i<2^{17}$。
- $\sum(r-l+1)\leqslant 2^{17}$。

## 思路
因为 $x$ 的二进制为的取值并不会互相影响，所以我们可以将 $x$ 和 $a$ 数组内的二进制位分离出来讨论。

因为异或操作可以将二进制为取反或者保持不变，所以我们可以统计出每一个二进制位的 $1$ 的数量。

如果 $a$ 数组内某一位为 $1$ 的数量的和与排列的数组内这一位为 $1$ 的数量，那么 $ans$ 这一位就应该是 $1$ 反之就是 $0$。
## AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
void io(){ios::sync_with_stdio(false);cin.tie(nullptr);}
const int N=2e5+5;
int l,r,s[30][2];
void solve(){
	cin>>l>>r;
	for(int i=l,x,y;i<=r;i++){
		cin>>x,y=i;
		for(int j=1;j<=20;j++){
			s[j][x&1]++;
			s[j][y&1]--;
			x>>=1,y>>=1;
		}
	}
	int ans=0;
	for(int i=20;i>=1;i--){
		ans=ans<<1|(s[i][1]!=0);
		s[i][1]=0;
	}
	cout<<ans<<'\n';
}
signed main(){io();
    int T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题意
给你一个长度为 $r+1$ 的数组，问是否可以通过一种 $\oplus x$ 的方式把它变成一个 $[0,r]$ 的排列。

### sol
因为是异或，所以 vp 时直接想到了按位考虑，然后你会发现他 $0,1$ 的出现是有规律的（废话。

然后我们观察 $0$ 的个数，你就会发现如果异或的 $x$ 这个数取了这一位，那么这一位上的 $0,1$ 都要反过来，然后按位模拟就行了。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int k,n,m,tot,a[300001],gcd=0,ans,x,t,l;
signed main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>l>>n;
		for(int i=0;i<=n;i++){
			cin>>a[i];
		}
		for(int j=0;j<=17;j++){
			int val1=0,val2=0;
			for(int i=0;i<=n;i++){
				if((a[i]>>j)&1) val1++;
				else val2++; 
			}
			int wtcl=1<<(j+1),wzdtcl=1<<j;
			int x=(n+1)/wtcl*wzdtcl+(min(wzdtcl,(n+1)%wtcl)),y=n+1-x;
			if(x==val1) ans|=(1<<j);
		}
		cout<<ans<<endl;
	}
}
```

---

