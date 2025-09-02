# 101 to 010

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_d

$ N $ 個のセルが一列に並んでいます。 何個かのセルはトークンを含んでいるかもしれません。 あなたは、 `0` と `1` からなる文字列 $ s $ が与えられます。 $ s $ の $ i $ 文字目が `1` のとき、(左から) $ i $ 番目のセルはトークンを一個含んでいます。 そうでないとき、トークンを含んでいません。

すぬけ君は、以下の操作をできる限り行いたいです。 各操作では、三個の連続するセルを選びます。 セルを左から $ X,\ Y,\ Z $ とします。 操作を行うためには、 $ X $ と $ Z $ の両方がトークンを含み、 $ Y $ はトークンを含んでいてはなりません。 次に、すぬけ君はこれらの二個のトークンを取り除き、新しいトークンを $ Y $ に一個置きます。

最適な操作の方法をしたとき、すぬけ君は何回操作を行えますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500,000 $
- $ |s|\ =\ N $
- $ s $ の各文字は `0` または `1` である。

### Sample Explanation 1

例えば、以下の方法で操作を二回行うことができます: - 最後の三個のセルに対し操作を行う。 トークンを表す文字列は `1010010` となる。 - 最初の三個のセルに対し操作を行う。 トークンを表す文字列は `0100010` となる。 操作の順番が重要であることに注意してください。 たとえば、最初に中央の三個のセルを選ぶと、それ以上操作を行えなくなります。

## 样例 #1

### 输入

```
7
1010101```

### 输出

```
2```

## 样例 #2

### 输入

```
50
10101000010011011110001001111110000101010111100110```

### 输出

```
10```

# 题解

## 作者：Tx_Lcy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_code_festival_2017_qualb_d)

## 思路

跟现有题解的思路不太一样。

首先这题显然要 $\rm DP$，设 $f_i$ 表示以 $i$ 为结尾，最优操作几次。

然后，我们发现形如 $101111$ 这样的串（左边一个 $10$，右边 $k$ 个 $1$）的贡献是 $k$，并且最后会变成 $000010$，$111101$ 这样的串同理，我们设这些串为好串。

我们找出以 $i$ 为右端点的极长的好串，显然最多只有两种可能，然后似乎就可以直接 $\rm DP$ 了，但是真的吗。

并不完全是，我们还需要考虑这种情况：$10111101$。

这样的最优方案是分成 $101$ 和 $11101$ 这两个串，而我们 $\rm DP$ 的时候不会考虑到这种情况。

再加一个转移就行了，代码非常好写。

时间复杂度 $\mathcal O(n)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
int const N=5e5+10;
int f[N],la[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;string s;
    cin>>n>>s,s=" "+s;
    for (int i=1;i<=n;++i){
    	la[i]=la[i-1];
    	if (s[i]=='0') la[i]=i;
	}
    for (int i=1;i<=n;++i){
    	f[i]=f[i-1];
    	if (s[i]=='0') continue;
    	int p=la[i];
    	if (s[p-1]=='0') continue;
    	if (p<2) continue;
    	f[i]=max(f[i],f[p-2]+i-p);
    	if (p+1==i){
    		int q=la[p-1];
    		f[i]=max(f[i],f[q]+p-q-1);
    		f[i]=max(f[i],f[q+1]+p-q-2);
		}
	}
    cout<<f[n]<<'\n';
    return 0;
}
```

---

## 作者：jijidawang (赞：1)

神仙 dp，太强了

令 $dp_i$ 表示 $1\sim i$ 最多换多少次，记录一个 $l_i$ 表示 $i$ 左边最接近的 $0$，$r_i$ 表示 $i$ 右边最接近的 $0$，从而：

[![yhtung.png](https://s3.ax1x.com/2021/02/19/yhtung.png)](https://imgchr.com/i/yhtung)
$$\tiny \color{grey}\text{好像洛谷博客不能直接输入汉字}$$

对于每一行的解释：
- 第一行：显然
- 第二行：若目前有 $\tt 101$，则换
- 第三行：若换完还有 $\tt101$，再换
- 第四、五行：同第二、三行 .

Code：
```cpp
using namespace std;
const int N=500500;
int n,dp[N],l[N],r[N];
string s;
int main()
{
	scanf("%d",&n); cin>>s;
	l[0]=(s[0]=='0'?0:-1); r[n]=n;
	for (int i=1;i<n;i++)
		if (s[i]=='1') l[i]=l[i-1];
		else l[i]=i;
	for (int i=n-1;i>=0;i--)
		if (s[i]=='1') r[i]=r[i+1];
		else r[i]=i;
	for (int i=0;i<=n;i++)
	{
		if (i) dp[i]=max(dp[i],dp[i-1]); // because line 47 .
		if ((i>=3)&&(s[i-1]=='1')&&(s[i-2]=='0')&&(s[i-3]=='1')) // pre
		{
			int j=l[i-3];
			dp[i]=max(dp[i],dp[j+1]+i-j-3);
			if (j!=i-4) dp[i]=max(dp[i],dp[j+2]+i-j-4); // 101 * 2
		}
		if ((i+3<=n)&&(s[i]=='1')&&(s[i+1]=='0')&&(s[i+2]=='1')) // suc ( nxt )
		{
			int j=r[i+2];
			dp[j]=max(dp[j],dp[i]+j-i-2);
			if (j!=i+3) dp[j-1]=max(dp[j-1],dp[i]+j-i-3); // 101 * 2;
		}
	} printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：isjwanglongLuoGU (赞：0)

## 思路：
观察到 $101$ 可变成 $010$，于是我们可以考虑将所有的 $101$ 变为 $010$。

那么我们考虑如何实现。

显然， DP。

首先注意到每次操作都会使得序列的 $1$ 的数量减少 $1$。
于是我们考虑维护序列中 $1$ 的数量，每次操作时将三个位置的 $1$ 的数量相加，如果为 $2$ 那么就将答案加 $1$ 并将三个位置的 $1$ 的数量分别减 $1$。

转移方程大概这样：
```cpp
dp[i+3]=max(dp[i+3],dp[i-j]+j+1)
dp[i+j+3]=max(dp[i+3+j],dp[i]+j+1)
dp[i+3]=max(dp[i+3],dp[i+2]
```


---

## 作者：kisshot (赞：0)

这道题很明显可以看出来是 $dp$。

 101 子串换完后变成 010 ，考虑到 $dp$ 的无后效性，似乎应该在 101 子串出现的第一个 1 位置变换，其实不然。

举个简单的例子：

$101011$

答案很明显可以看出来是 2 ，分别在第 3 , 4 位置开头的 101 子串变换。

可见应该在 101 子串出现的末尾的 1 开始判断变换。

但考虑到可能有些 101 子串在之前没有换，因此加入一个变量 pre 记录这个 101 子串出现的位置，以便之后查找变换。

之后很容易就可以得出转移方程：

$\begin{cases}ans[i]=ans[i-1]\\ans[i]=ans[make0[i-2]+(i-2-make0[i-2])]\\ans[i]=ans[make0[i-2]+1]+(i-2-(make0[i-2]+1))\\ans[i]=Max(ans[i],ans[pre-3]+(i-pre+1))\end{cases}$

其中 make0 数组指的是上一个 0 出现的位置。

再举个简单的例子：

0111101

咱们依次变换：

| 0111101 	|
| :-------: |
| 0111010 	|
| 0110100 	|
| 0101000	|
| 0010000 	|

4 个 1 ，共变换 4 次，因此变换次数是 101 子串起始位置到上一个 0 的距离。
即第二种情况。

但变换到最后一个时，可能另有最优情况，比如：

110111101

当变换成 110101000 时，就不该继续变换了，而是变成 101101000 。
即第三种情况。

在上面三种情况之后，还有如果还有 101 子串，则变换，即第四种情况。


完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define re register
#define ll long long

inline ll read(){
	ll x=0,f=0;char ch=getchar();
	while(ch>'9'||ch<'0')f|=ch=='-',ch=getchar();
	while(ch<='9'&&ch>='0')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}//快读 

const int N=500000+1;

inline ll Max(ll x,ll y){return x>y?x:y;}//比大小 

ll n,s[N],make0[N],ans[N];
//make0数组记录0出现的位置(可能是当前位置或之前位置) 
//ans数组记录从1到i的最佳次数,ans[n]即为答案 

int main(){
	
	n=read();
	for(re ll i=1;i<=n;++i){
		scanf("%1lld",&s[i]);
	}//读入,%1lld保证每次只读入一个数字 
	
	for(re ll i=1;i<=n;++i){
		if(s[i]==0){
			make0[i]=i;
		}
		else make0[i]=make0[i-1];
	}//处理make0数组
	
	ll pre=0;
	for(re ll i=1;i<=n;++i){ 
	
		if(i>=3&&s[i]==1&&s[i-1]==0&&s[i-2]==1){
			pre=i;
			//记录以i结尾的101子串出现的位置,但是不换。 
		}
		
		ans[i]=ans[i-1];
		//先更新答案,保留上次最佳状态 
		
		if(i>=3&&s[i-2]==1&&s[i-1]==0&&s[i]==1){
			ans[i]=max(ans[i],ans[make0[i-2]]+(i-2-make0[i-2]));
			//若此时101子串以i结尾,此时该子串可换 
			//make0[i-2]指的是上一次出现0的地方,(i-2-make0[i-2])指的是这个子串到上一个0的距离 
           	ans[i]=max(ans[i],ans[make0[i-2]+1]+(i-2-(make0[i-2]+1)));
           	//这行可以看做是上一行的前置情况,即留一个101子串不换 
		}
		
		if(pre>make0[i]){
			ans[i]=Max(ans[i],ans[pre-3]+(i-pre+1)); 
			//考虑换完之后还有101子串,则继续换 
		}
	}
	printf("%lld\n",ans[n]);//输出答案 
	return 0;
}
```


---

