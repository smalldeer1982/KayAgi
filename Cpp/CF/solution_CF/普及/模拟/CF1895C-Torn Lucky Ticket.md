# Torn Lucky Ticket

## 题目描述

A ticket is a non-empty string of digits from $ 1 $ to $ 9 $ .

A lucky ticket is such a ticket that:

- it has an even length;
- the sum of digits in the first half is equal to the sum of digits in the second half.

You are given $ n $ ticket pieces $ s_1, s_2, \dots, s_n $ . How many pairs $ (i, j) $ (for $ 1 \le i, j \le n $ ) are there such that $ s_i + s_j $ is a lucky ticket? Note that it's possible that $ i=j $ .

Here, the + operator denotes the concatenation of the two strings. For example, if $ s_i $ is 13, and $ s_j $ is 37, then $ s_i + s_j $ is 1337.

## 样例 #1

### 输入

```
10
5 93746 59 3746 593 746 5937 46 59374 6```

### 输出

```
20```

## 样例 #2

### 输入

```
5
2 22 222 2222 22222```

### 输出

```
13```

## 样例 #3

### 输入

```
3
1 1 1```

### 输出

```
9```

# 题解

## 作者：无钩七不改名 (赞：12)

### 题意

大概就是给出一些纯数字字符串，每两个字符串可以首尾拼接成一个新的字符串。求有多少对不同的字符串使得拼接后的字符串长度为偶数且前半部分各位数相加得到的数的大小等于后半部分的各位数相加得到的数的大小。

### 解法

可以发现一共有三种拼接方法：两个等长的，一长一短，或者一短一长。

我们设 $num_{i,j}$ 表示一共有 $i$ 位且各位数之和为 $j$ 的字符串的数量。

设 $b_{i,j}$ 为被分成两段且右边比左边长度大 $i$，和大 $j$ 的字符串的数量。

（其实两个数组是可以合并的，这里分开是怕思路乱了。）

我们枚举放在左边的字符串，设当前字符串长度为 $i$，各位数之和为 $j$。对三种情况分类讨论：

+ 两个字符串等长：答案为 $num_{i,j}$。

+ 左边字符串短于右边字符串：答案为 $b_{i,j}$，因为这样就把右边比左边多的都弥补了。

+ 左边字符串长于右边字符串：我们可以枚举被割在右边的字符串子串长度，通过 $num$ 数组统计答案即可。和第二种情况同理。

具体可以看代码。

### 赛时代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N=200005,M=55;
 
int n,a[N];
int b[6][M],num[6][M];
int cc[6],cnt;
long long ans;
 
int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
} 
 
int main(){
	n=read();
	for(int i(1);i<=n;++i){
		a[i]=read();
		cnt=0;int j=a[i];
		int sum=0;
		while(j){
			cc[++cnt]=j%10;
			sum+=cc[cnt];
			j/=10;
		}int sum2=0;
		++num[cnt][sum];
		for(int j(1);j<cnt;++j){
			sum2+=cc[j];
			if(cnt-j>=j||sum2<=sum-sum2)continue;
			++b[j-(cnt-j)][sum2-(sum-sum2)];
		}
		//cout<<i<<": "<<sum<<'\n';
	}
	//定义 b_{i,j} 为 右边-左边 长度为 i ，大小为 j的数量 
	for(int i(1);i<=n;++i){
		cnt=0;int j=a[i];
		int sum=0;
		while(j){
			cc[++cnt]=j%10;
			sum+=cc[cnt];
			j/=10;
		}
		ans+=num[cnt][sum];
		ans+=b[cnt][sum];
		int sum2=0;
		for(int j(1);j*2<=cnt;++j){
			sum2+=cc[j];
			if(sum2*2>sum)break;
			ans+=num[cnt-j-j][sum-sum2*2];
			//cout<<cnt-j-j<<" "<<sum-sum2<<'\n';
		}
	//	cout<<i<<" ans:"<<ans<<" "<<b[cnt][sum]<<'\n';
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：IKUN314 (赞：5)

# Torn Lucky Ticket
## 约定


约定对于字串 $a$，$|a|$ 表示 $a$ 的长度， $a_i$ 表示 $a$ 中第 $i$ 个数码的值。

字串间的 $+$ 运算表示字串拼接，即 $a+b$ 表示将 $b$ 的头部接在 $a$ 的尾部得到的字符串，如 $\texttt{13}+\texttt{37}=\texttt{1337}.$

## 题意

给你 $n (1\le n\le 2\cdot10^5)$ 个非空字串 $s_1,s_2,\dots,s_n$，保证 $s_{i,j}\in[0,9]\cap \mathbb{N},1\le |s_i|\le 5$。 

求有多少个二元组 $(i,j)$ 满足：

1. $1\le i,j\le n$，注意这代表 $i<j,i=j,i>j$ 都是合法的，且当 $i\neq j$ 时 $(i,j)$ 与 $(j,i)$ 算作不同方案；
2. 设字串 $t=s_i+s_j$，它满足：
	- ${|t|}$ 是偶数
   - $\sum_{k=1}^{\frac{|t|}{2}}t_k=\sum_{k=\frac{|t|}{2}+1}^{|t|}t_k=\dfrac{1}{2}\sum_{k=1}^{|t|}t_k$，即 $t$ 的前一半数码的值之和与后一半数码的值之和相等，都为整串 $t$ 的数码的值之和的一半。
   
## 解题思路

考虑对于字串 $s_i$ 计算它作为二元组的第一元和第二元且第一元和第二元不相等时的总贡献 $f_i$，显然 $ans=\underset{(i,i)\text{ 形式的二元组个数}}{n}+\sum_{i=1}^nf_i$。考虑如何计算 $f_i$。

我们看到限制 2，发现当将拼起来的字串分成两半时，若长度不同，则二元组中长度长的字串一定会被分割。于是我们可以先对 $s_1,s_2,\dots,s_n$ 以长度为第一关键字从小到大排序，可以证明这不影响答案。枚举 $s_i$ 时强制跟前面长度不超过 $|s_i|$ 的字串 $s_k(1\le k<i)$ 组合，至于到底是 $(i,k)$ 还是 $(k,i)$ 之后再讨论。
 
于是对于字串 $s_i$ 枚举从哪个位置 $j(1\le j\le |s_i|)$ 断开，其中 $s_{i,j}$ 是包含的。另外在之前要预处理出所有 $s_i$ 的前缀和 $pre_i$ 和后缀和 $suf_i$。那么

$$
\begin{aligned}
f_i=\sum_{j=1}^{|s_i|}\sum_{k=1}^{i-1}&\underbrace{[\underset{\text{左半部分长度}}{|s_k|+(j-1)}=\underset{\text{右半部分长度}}{|s_i|-j+1}\land \underset{\text{左半部分总和}}{suf_{k,1}+pre_{i,j-1}}= \underset{\text{右半部分总和}}{{suf}_{i,j}}]}_{{(k,i)\text{ 形式的二元组的贡献}}}\\&+\underbrace{[\underset{\text{右半部分长度}}{|s_k|+(|s_i|-j)}=\underset{\text{左半部分长度}}{j}\land \underset{\text{右半部分总和}}{suf_{k,1}+suf_{i,j+1}}=\underset{\text{左半部分总和}}{pre_{i,j}}]}_{(i,k)\text{ 形式的二元组的贡献}}
\end{aligned}
$$

最里层求和的意思就是满足 $(k,i)$ 的 $k$ 的个数与满足 $(i,k)$ 的 $k$ 的个数的总和。直接这么找是 $O(5n^2)=O(n^2)$ 的，显然无法通过，考虑优化掉最里面的那层循环。我们把式子中间的那两个条件整理成成对 $k$ 的限制，就是：

$$
\begin{aligned}
&[|s_k|=|s_i|-j+1-(j-1)>0\land suf_{k,1}= {suf}_{i,j}-pre_{i,j-1}>0]\\&+[|s_k|=j-(|s_i|-j)>0\land suf_{k,1}=pre_{i,j}-suf_{i,j+1}>0 \space]
\end{aligned}
$$

发现这其实就是求在 $i$ 前面的 $|s_k|$ 和 $suf_{k,1}$  为指定值的 $k$ 的个数，一看数据范围小的很呐，最坏一个 $5$ 一个 $9\times5=45$，考虑使用桶动态维护。开一个桶 $buc$，令 $buc_{i,j}$ 表示长度为 $i$，总和（字串 $s_x$ 的总和就等于 $suf_{x,1}$）为 $j$ 的字串个数。则对于每一轮 $s_i (1\le i\le n)$ 的枚举，进行如下维护：

1. 枚举断开位置 $j(1\le j\le |s_i|)$，随后累加 $f_i$：
	- 若 $|s_i|-j+1-(j-1)>0\land {suf}_{i,j}-pre_{i,j-1}>0$，更新 $f_i\leftarrow f_i+buc_{(|s_i|-j+1-(j-1)),({suf}_{i,j}-pre_{i,j-1})}$;
   - 若 $j-(|s_i|-j)>0 \land pre_{i,j}-suf_{i,j+1}>0$，更新 $f_i\leftarrow f_i+buc_{(j-(|s_i|-j)),(pre_{i,j}-suf_{i,j+1})}$
   - 上两步中判断长度与总和大于 $0$ 是必要的，否则不合题意且会出现负下标。
2. 更新 $buc_{|s_i|,suf_{i,1}}\leftarrow buc_{|s_i|,suf_{i,1}}+1$.

最后统计答案 $ans={n}+\sum_{i=1}^nf_i$ 即可。

排序复杂度 $O(n\log n)$，预处理与计算的复杂度 $O(5n)$。总时间复杂度为 $O(n\log n)$。不慢不快吧，对于这道题是绰绰有余。瓶颈主要在排序上，其实有不用排序的方法，留给读者自行思考。

**别忘记开 `long long` ！！**

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//别忘记开 long long！！！
constexpr int N=2e5+10;
int n,a[N];
int dig[N][10],tmp[10];
int pre[N][10],ful[N][10];
int f[N],ans,buc[10][60];
bool cmp(int x,int y){
    int lenx=log10(x)+1;
    int leny=log10(y)+1;
    //这里计算长度偷了点懒哈哈，正规来写的话可以输入时用结构体把值、串、长度都存起来，而不是每次计算log10。
    if(lenx==leny) return x<y;
    return lenx<leny;
}
signed main(){
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n,cmp); //以长度为第一关键字排序
    for(i=1;i<=n;i++){ // 预处理前缀后缀和
        int it=0;
        while(a[i]){
            tmp[++it]=a[i]%10;
            a[i]/=10;
        }
        dig[i][0]=it;
        for(j=1;j<=it;j++){
            dig[i][j]=tmp[it-j+1];
            pre[i][j]=pre[i][j-1]+dig[i][j];
        }
        for(j=it;j>=1;j--){
            ful[i][j]=ful[i][j+1]+dig[i][j];
        }
    }
    for(i=1;i<=n;i++){
        int len=dig[i][0];
        for(j=1;j<=len;j++){ //累加 f[i]
            if(len-j+1-(j-1)>0&&ful[i][j]-pre[i][j-1]>0)f[i]+=buc[len-j+1-(j-1)][ful[i][j]-pre[i][j-1]];
            if(j-(len-j)>0&&pre[i][j]-ful[i][j+1]>0) f[i]+=buc[j-(len-j)][pre[i][j]-ful[i][j+1]];
        }
        buc[len][ful[i][1]]++;
    }
    ans=n;
    for(i=1;i<=n;i++){ //统计答案
        ans+=f[i];
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：DerrickLo (赞：4)

我们可以枚举合成后的串的长度，然后枚举合成的两个串中较长的串的长度，接着就能算出这个串的和应该是多少，然后算一下另一个串的个数有多少个，相加就是答案。

```cpp
#include<bits/stdc++.h> 
#define int long long 
using namespace std;
int n,s[200005],ans;
vector<int> ve[10][50];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		int now=0,aa=s[i],sum=0;
		while(aa){
			now++;
			sum+=aa%10;
			aa/=10;
		}
		ve[now][sum].emplace_back(s[i]);
	}
	ans=n;
	for(int i=2;i<=10;i+=2){
		int now=i/2;
		for(int j=now;j<i;j++){
			int k=i-j;
			for(int kk=0;kk<=45;kk++)for(int v:ve[j][kk]){
				int noww=0,aa=v,summ=0,sum2=0;
				while(noww<now){
					summ+=aa%10,noww++;
					aa/=10;
				}
				while(aa){
					sum2+=aa%10,aa/=10;
				}
				ans+=ve[k][summ-sum2].size();
				if(j==now)ans--;
				if(j==now)continue; 
				noww=0,aa=v,summ=0,sum2=0;
				while(noww<j-now){
					sum2+=aa%10,noww++;
					aa/=10;
				}
				while(aa)summ+=aa%10,aa/=10;
				ans+=ve[k][summ-sum2].size();
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ax_by_c (赞：3)

# 题目描述

定义“ticket”为一个由数字一到九组成的串。

定义“lucky ticket”为满足以下两个条件的“ticket”：

- 长度为偶数

- 前半部分数字和与后半部分数字和相等。

现在给出若干个长度不超过五且由数字一到九组成的串 $s_1,s_2,\dots,s_n$，问有多少的 $(i,j)$ 使得把 $s_j$ 拼在 $s_i$ 后面时得到的是“lucky ticket”。

$(i,i)$ 的情况是算的，$(j,i)[j\operatorname{>} i]$ 的情况也是算的。

# 解题思路

显然这是一道计数题。

为了防止麻烦，我是把长度不同的情况和长度相同的情况分开算的。

## 长度不同的情况

当长度不同的时候，一定有一个串是更长的。

所以枚举每一个串，然后计算其为第一部分且为长串的答案，并计算其为第二部分且为长串的答案。

那么怎么算呢？

假设要算一个第一部分且为长串的串的答案。

那么既然它是长的，所以按照拼接后的中点分割一定能够把它分为两段。

所以枚举一个合法的中点。

然后此时前半段就已经确定了长度和数字和。

而后半段有了若干的长度和数字和。

那么按前半段为基准，就可以计算出后半段还需要的长度和数字和。

所以拼上去的串就要刚好符合后半段还需要的长度和数字和。

此时问题变为给出长度和数字和求串数。

预处理一下即可。

第二部分且为长串的答案计算方法同理。

## 长度相同的情况

这时就好做多了。

枚举每一个串，然后计算其为第一部分的答案。

显然，长度和数字和已确定，直接求出这样的串数即可。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
typedef long long ll;
int n;
int a[N];
int lth(int x)
{
	if(!x)return 0;
	return lth(x/10)+1;
}
int su(int x)
{
	if(!x)return 0;
	return su(x/10)+x%10;
}
int las(int x,int p)
{
	if(!p)return 0;
	return las(x/10,p-1)+x%10;
}
ll mp[10][100];
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		mp[lth(a[i])][su(a[i])]++;
	}
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		int lt=lth(a[i]);
		int s1,s2,nd,nl,lp;
		for(int j=1;j<lt;j++)
		{
			if(2*j<=lt)
			{
				continue;
			}
			s2=las(a[i],lt-j);
			s1=su(a[i])-s2;
			nl=2*j-lt;
			nd=s1-s2;
			ans+=mp[nl][nd];
		}
		for(int j=1;j<lt;j++)
		{
			if(2*j<=lt)
			{
				continue;
			}
			s2=las(a[i],j);
			s1=su(a[i])-s2;
			nl=2*j-lt;
			nd=s2-s1;
			ans+=mp[nl][nd];
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans+=mp[lth(a[i])][su(a[i])];
	}
	printf("%lld\n",ans);
}
int main()
{
	solve();
	return 0;
}
```

别忘了开 longlong 哦。

---

## 作者：ZZZZZZZF (赞：1)

# 题意

定义一个 trick 序列满足如下性质：

1. 长度为偶数。

2. 前一半数字的和等于后一半数字的和。

形式化的讲，对于一个序列 $s$，若满足：

1. $L = 2\times k\quad k \in Z$
2. $\sum\limits_{i = 1}^n s_i = \sum\limits_{i = n+1}^{2n} s_i$

则称 $s$ 为 trick 序列。

给定 $n$ 个长度不多于 $5$ 的数字序列。

求有序数对 $(i,j)$ 的个数，使 $s_i+s_j$ 是一个 trick 序列。

注意：$(i,i)$ 只算一次

$n \le 2\times 10^5$

# 思路

分类讨论 $+$ 暴力

对于每一个给定的序列，枚举中点的位置，可以计算出需要拼接的序列的长度与各位之和，找出符合要求的序列数量即可。

由于序列长度不超过 $5$，各位之和不超过 $50$，可以用桶储存各个序列的长度与各位和。 ~~我竟然还想用二分查找~~

时间复杂度 $O(n)$。

注意最差情况下答案可能会超过 int 范围，需要开 long long。

细节较多，看代码吧。

# Code
```cpp
#include<BITS/stdc++.h>
#define N 200010

using namespace std;

//不开 long long 见祖宗
long long ans;
int n;

//sum：序列桶 num：记录每一位 ssum：记录每个序列的和
//sum[i][j]：和为i，长度为j的序列数量
int sum[100][10],num[N][10],ssum[N];

int main(){

    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        int a,d = 0,s = 0;
        scanf("%d",&a);
        while(a!=0){
            num[i][++d] = a % 10;
            s+=a%10;
            a/=10;
        }
        ssum[i]=s;
        sum[s][d] += 1;
        
        //序列长度记在第六位
        num[i][6] = d;
    }
/*输入调试
    for(int i = 1;i<=100;i++){
        for(int j = 1;j<10;j++){
            if(sum[i][j])
                printf("%d %d  %d\n",i,j,sum[i][j]);
        }
    }

    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=5;j++){
            printf("%d ",num[i][j]);
        }
        printf("\n");
    }
*/

    //将其他序列接到后面
    for(int i = 1;i<=n;i++){
        int dgt = num[i][6];
        for(int d = 1;d<=dgt/2;d++){
            int sum1 = 0,sum2 = 0;
            for(int j = 1;j<=d;j++)
                sum1+=num[i][j];
            for(int j = d+1;j<=dgt;j++)
                sum2+=num[i][j];
            if(sum2>sum1){
                ans+=sum[sum2-sum1][dgt-d-d];
            }
        }
    }

    //将其他序列接到前面后面
    for(int i = 1;i<=n;i++){
        int dgt = num[i][6];
        
        //此处d为分割点的位置，当d = dgt时，表示另一半为空
        //此时统计出的答案为不分割的情况和接自己的情况
        //只计算一次
        for(int d = dgt/2+1;d<=dgt;d++){
            int sum1 = 0,sum2 = 0;
            for(int j = 1;j<=d;j++)
                sum1+=num[i][j];
            for(int j = d+1;j<=dgt;j++)
                sum2+=num[i][j];
            if(sum2<sum1){
                //if(sum[sum1-sum2][d+d-dgt])//printf("%d %d  %d\n",i,d,sum[sum2-sum1][dgt-d-d]);
                ans+=sum[sum1-sum2][d+d-dgt];
            }
        }
    }

    printf("%lld",ans);
    return 0;
}

```

---

## 作者：Didncan_yu (赞：1)

为避免歧义，$a$ 数组为整数变量数组，$a_i + a_j$ 为二者之和。如 $a_i = 1,a_j = 3,a_i + a_j = 4$。题意中形式表述为 “$a_i$ 后拼接 $a_j$”，如 $a_i = 1,a_j = 3,a_i + a_j = 13$。

### 题目大意

定义幸运彩票为长度为偶数，且前半部分数字和等于后半部分数字和（字符串仅包含非 $0$ 数字）的字符串。

现在可以选取二元对 $(i,j)(1 \le i,j \le n)$，问在 $a_i$ 后拼接 $a_j$，使其为幸运彩票的方案总数。

注：$(i,j) \ne (j,i)$。

### 思路分析

定义 $b_i$ 为字符串 $a_i$ 的长度。

用 $dls_{i,j}$ 表示在**当前范围内**长度为 $i$，各位数字之和为 $j$ 的数有多少。

接下来由于 $1 \le i \le 5$，直接按 $i$ 分类暴力做。

规定 $a_i$ 确定后，$b_j \le a_j$，防止重复计算。

- $i=1$，这时只能挑选长度为 $1$ 的 $a_j$（如果 $b_j > a_j$ 就应按 $b_j$ 长度做）。

- $i=2$，这时只能挑选长度为 $2$ 的 $a_j$（同上，不再展开）。

- $i=3$，这时能挑选长度为 $3$ 的 $a_j$，也可以挑选长度为 $1$ 的 $a_j$。例如：
```
201 1
```
此时前半段为 $2+0=2$，即 $201$ 去掉个位，此时 $b_j=2+0-1=1$。

注意分前后两种拼接方法。

- $i=4$，这时能挑选长度为 $4$，长度为 $2$ 的 $a_j$。

- $i=5$，这时能挑选长度为 $5$ 或 $3$ 或 $1$ 的 $a_j$。

这部分代码如下：
```cpp
for(int i=1;i<=n;i++){
		pair<int,int>t1=ktr(a[i]);//t1.first 为各位数字之和，t1.second 为长度  
		switch(t1.second){
		case 1:
			ans+=dls[1][t1.first]*2;
			break;
		case 2:
			ans+=dls[2][t1.first]*2;
			break;
		case 3:
			ans+=dls[3][t1.first]*2;
			ans+=dls[1][t1.first-get_k(a[i],1)*2];
			ans+=dls[1][t1.first-get_k(a[i],3)*2];
			break;
		case 4:
			ans+=dls[4][t1.first]*2;
			ans+=dls[2][t1.first-get_k(a[i],1)*2];
			ans+=dls[2][t1.first-get_k(a[i],4)*2];
			break;
		case 5:
			ans+=dls[5][t1.first]*2;
			ans+=dls[3][t1.first-get_k(a[i],1)*2];
			ans+=dls[3][t1.first-get_k(a[i],5)*2];
			ans+=dls[1][t1.first-get_k(a[i],1)*2-get_k(a[i],2)*2];
			ans+=dls[1][t1.first-get_k(a[i],4)*2-get_k(a[i],5)*2];
			break;
		}
		dls[t1.second][t1.first]++;
		ans++;
	}
```
但你会发现连样例都过不了……
```
2
333 3
```
这组数据中，$3$ 没有与 $333$ 配对，而如果从 $3$ 找到 $333$ 又要较高的复杂度，所以我们的解决方案是：
```cpp
sort(a+1,a+n+1);
```
在 $a$ 数组成员仅是位置改变的情况下，并不影响答案。现在从 $333$ 找到 $3$ 是可以以 $i=3$ 情况处理的。
### 最终代码
```cpp
#include<bits/stdc++.h>
#define int long long //CF题必备
using namespace std;
inline int read();
inline void write(long long n);
inline string str_read();
inline void str_write(string a);
void slove();
const int MAX=2e5+7;
int n,a[MAX],ans;
map<int,int>dls[6];
pair<int,int>ktr(int a){
	int sum=0,dk=0;
	while(a){
		sum+=a%10;
		a/=10;
		dk++;
	}
	return make_pair(sum,dk);
}
int get_k(int x,int s){
	for(int i=1;i<s;i++)x/=10;
	return x%10;
}
signed main(){
	slove();
	return 0;
}
void slove(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		pair<int,int>t1=ktr(a[i]);
		switch(t1.second){
		case 1:
			ans+=dls[1][t1.first]*2;
			break;
		case 2:
			ans+=dls[2][t1.first]*2;
			break;
		case 3:
			ans+=dls[3][t1.first]*2;
			ans+=dls[1][t1.first-get_k(a[i],1)*2];
			ans+=dls[1][t1.first-get_k(a[i],3)*2];
			break;
		case 4:
			ans+=dls[4][t1.first]*2;
			ans+=dls[2][t1.first-get_k(a[i],1)*2];
			ans+=dls[2][t1.first-get_k(a[i],4)*2];
			break;
		case 5:
			ans+=dls[5][t1.first]*2;
			ans+=dls[3][t1.first-get_k(a[i],1)*2];
			ans+=dls[3][t1.first-get_k(a[i],5)*2];
			ans+=dls[1][t1.first-get_k(a[i],1)*2-get_k(a[i],2)*2];
			ans+=dls[1][t1.first-get_k(a[i],4)*2-get_k(a[i],5)*2];
			break;
		}
		dls[t1.second][t1.first]++;
		ans++;
	}
	write(ans);
	return ;
}
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void write(long long n){
	if(n<0){putchar('-');n=-n;}
	if(n>9){write(n/10);}
	putchar(n%10+'0');
}
```
[赛时AC](https://codeforces.com/contest/1895/submission/231204815)

---

