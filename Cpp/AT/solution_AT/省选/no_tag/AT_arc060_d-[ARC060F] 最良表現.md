# [ARC060F] 最良表現

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc060/tasks/arc060_d

$ x $ を長さ $ 1 $ 以上の文字列とします。 いかなる文字列 $ y $ および $ 2 $ 以上の整数 $ k $ に対しても、 $ y $ を $ k $ 回繰り返した文字列が $ x $ と異なるならば、 $ x $ を*良い文字列*であると呼ぶことにします。 例えば、`a`, `bbc`, `cdcdc` などは良い文字列ですが、 `aa`, `bbbb`, `cdcdcd` などは良い文字列ではありません。

$ w $ を長さ $ 1 $ 以上の文字列とします。 $ m $ 項からなる列 $ F=(\,f_1,\,f_2,\,...,\,f_m) $ について、 次の条件がともに満たされるならば、$ F $ を $ w $ の*良い表現*と呼ぶことにします。

- すべての $ i\ \,\ (1\ \leq\ i\ \leq\ m) $ について、$ f_i $ は良い文字列である。
- $ f_1,\,f_2,\,...,\,f_m $ をこの順に連結すると $ w $ になる。

例えば、$ w= $`aabb` の場合、$ w $ の良い表現は次の $ 5 $ つとなります。

- $ ( $`aabb`$ ) $
- $ ( $`a`$ , $`abb`$ ) $
- $ ( $`aab`$ , $`b`$ ) $
- $ ( $`a`$ , $`ab`$ , $`b`$ ) $
- $ ( $`a`$ , $`a`$ , $`b`$ , $`b`$ ) $

文字列 $ w $ の良い表現のうち、項数 $ m $ が最小であるものを、 $ w $ の*最良表現*と呼ぶことにします。 例えば、$ w= $`aabb` の最良表現は $ ( $`aabb`$ ) $ の $ 1 $ つのみとなります。

文字列 $ w $ が与えられます。次の $ 2 $ つを求めてください。

- $ w $ の最良表現の項数
- $ w $ の最良表現の総数を $ 1000000007\ \,\ (=10^9+7) $ で割った余り

なお、$ w $ に対し、良い表現が存在することは保証されます。

## 说明/提示

### 制約

- $ 1\ \leq\ |w|\ \leq\ 500000\ \,\ (=5\ \times\ 10^5) $
- $ w $ は英小文字 (`a`-`z`) のみからなる文字列である

### 部分点

- $ 1\ \leq\ |w|\ \leq\ 4000 $ を満たすデータセットに正解した場合は、$ 400 $ 点が与えられる。

### Sample Explanation 2

\- この入力に対しては、項数が $ 2 $ の最良表現が以下の $ 3 $ 通り存在します。 - $ ( $`b`$ , $`cbc`$ ) $ - $ ( $`bc`$ , $`bc`$ ) $ - $ ( $`bcb`$ , $`c`$ ) $

## 样例 #1

### 输入

```
aab```

### 输出

```
1
1```

## 样例 #2

### 输入

```
bcbc```

### 输出

```
2
3```

## 样例 #3

### 输入

```
ddd```

### 输出

```
3
1```

# 题解

## 作者：chenxia25 (赞：12)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT2040) & [AtCoder题目页面传送门](https://atcoder.jp/contests/arc060/tasks/arc060_d)

>若一个字符串$a$有$<|a|$的循环节，我们称它是循环的。给定一个字符串$a,|a|=n$，求它最少能被分成多少个子串，使得每个分成的子串都不循环，并求分成最少数量个子串的方案数。第$2$问答案对$10^9+7$取模。

>$n\in\left[1,5\times10^5\right]$。

首先，如果$a$不循环，那么$2$问的答案显然分别是$1,1$。

先介绍一下字符串判循环的基本方法：字符串$x$有循环节$len$当且仅当$len\mid |x|,x_{1\sim |x|-len}=x_{len+1\sim|x|}$。证明：$x_{1\sim |x|-len}=x_{len+1\sim|x|}$，即$\forall i\in[1,|x|-len],x_i=x_{i+len}$。显然$len$个字符是一个周期。又因为$len\mid |x|$，所以$len$是$x$的循环节。得证。于是可以用这个结论判$a$是否循环。

接下来讨论$a$循环的情况。分$2$种情况：
1. $a$的最小循环节为$1$。此时显然只能分成$n$份，方案数为$1$；
2. $a$的最小循环节$>1$。下面专门讨论这种情况。

可以发现，若将$a$分成$a_{1\sim n-1},a_{n\sim n}$这$2$段，是满足题意的。$a_{n\sim n}$显然不循环。$a_{1\sim n-1}$可以看作一个循环字符串删除了后$x$（$x<$此字符串的最小循环节）个字符后得到的字符串。我们称这类字符串是不完整循环的。容易~~（个p）~~证明，不完整循环的字符串一定是不循环的。

证明：反证法。设字符串$x$是一个不完整循环的字符串。设$len$为最小不完整循环节，即$len$是最小的满足$len\nmid|x|,x_{1\sim |x|-len}=x_{len+1\sim|x|}$的数。假设$x$也是循环的，那么设$len'$为最小循环节，即$len'$是最小的满足$len'\mid|x|,x_{1\sim |x|-len'}=x_{len'+1\sim|x|}$的数。显然$len\neq len'$。

引理：若存在$2$个数$len,len'(len<len')$满足$x_{1\sim |x|-len}=x_{len+1\sim|x|},x_{1\sim |x|-len'}=x_{len'+1\sim|x|}$，那么必存在第$3$个数$len''=len'-len$满足$x_{1\sim |x|-len''}=x_{len''+1\sim|x|}$。

证明：

1. $x_{1\sim |x|-len}=x_{len+1\sim|x|},x_{1\sim |x|-len'}=x_{len'+1\sim|x|}$，即$\forall i\in[1,|x|-len],x_i=x_{i+len},\forall i\in[1,|x|-len'],x_i=x_{i+len'}$。显然，$\forall i\in[1,|x|-len'],x_i=x_{i+len}=x_{i+len'}$。所以$\forall i\in[len+1,|x|-len'+len],x_i=x_{i+len'-len}$。即$\forall i\in[len+1,|x|-len''],x_i=x_{i+len''}$；
2. $x_{1\sim |x|-len}=x_{len+1\sim|x|},x_{1\sim |x|-len'}=x_{len'+1\sim|x|}$，即$\forall i\in[len+1,|x|],x_i=x_{i-len},\forall i\in[len'+1,|x|],x_i=x_{i-len'}$。显然，$\forall i\in[len'+1,|x|],x_i=x_{i-len}=x_{i-len'}$。所以$\forall i\in[1,|x|-len'],x_{i-len+len'=x_i}$。即$\forall i\in[1,|x|-len'],x_i=x_{i+len''}$。~~（仿照上例显然）~~

综上，$\forall i\in[len+1,|x|-len'']\cup[1,|x|-len']=[\min(len+1,1),\max(|x|-len'',|x|-len')]=[1,|x|-len''],x_i=x_{i+len''}$。即$x_{1\sim |x|-len''}=x_{len''+1\sim|x|}$。得证。

根据引理和辗转相除法可知，对于$len''=\gcd(len,len')$，$x_{1\sim |x|-len''}=x_{len''+1\sim|x|}$。分$2$种情况：
1. $len'\mid len$。显然$x_{1\sim len}$有循环节$len'$，所以任何以$x_{1\sim len}$循环的字符串一定有循环节$len'$。所以任何以$x_{1\sim len}$循环的字符串的最小循环节一定$\leq len'$。设$t$为最小的满足$t\cdot len\geq|x|$的整数。因为$len'\mid|x|,len'\mid len$，所以$len'\mid t\cdot len-|x|$。又因为$len\nmid|x|$，所以$t\cdot len\neq|x|$，所以$t\cdot len-|x|>0$。所以$t\cdot len-|x|\geq len'$。即$x$是一个循环字符串删除了至少后$len'$个字符后得到的。又任何以$x_{1\sim len}$循环的字符串的最小循环节一定$\leq len'$，与不完整循环的定义中“$x<$此字符串的最小循环节”矛盾；
2. $len'\nmid len$。显然$\gcd(len,len')<len'$。又显然$\gcd(len,len')\mid len'$，所以$\gcd(len,len')$是$x$更小的循环节，与$len'$是最小循环节矛盾。

综上，$2$种情况都推出矛盾。得证。~~（怎么证明了这么长啊）~~

所以一定存在将$a$分成$2$段的方法。接下来要做的只是计数。不难发现，分成$2$段的方法数不会超过$n-1$（所以说“对$10^9+7$取模”是个幌子），我们可以枚举断点，一个一个判断。

考虑怎么判断某个前/后缀是否循环。显然可以用Z算法预处理出每个后缀与$a$的LCP$lcP_i$和每个前缀与$a$的LCS$Lcs_i$，然后判断时枚举要判断的前/后缀长度的所有真因数作为循环节，每个真因数$\mathrm O(1)$判断是否循环节。这看起来枚举每个数的真因数都要$\mathrm O(\sqrt n)$，总时间$\mathrm O(n\sqrt n)$，然鹅其实根本不用这么慢。如果每次枚举的都正好是真因数的话，那么时间复杂度就是$1\sim n$之间（真因数，真倍数）对的个数，考虑计算每个数当作真因数对总对数的贡献，那么时间复杂度就是$\mathrm O\!\left(\sum\limits_{i=1}^n\dfrac ni\right)$。这是$n$与第$n$个调和数的乘积。由于第$n$个调和数与$\ln n$的差收敛于欧拉常数，所以第$n$个调和数可以认为等于$\mathrm O(\ln n)$。所以时间复杂度就是$\mathrm O(n\ln n)$。至于如何做到“每次枚举的都正好是真因数”，枚举每个数当作真因数，然后将它压进每个真倍数的真因数序列里，这样预处理即可。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=500000;
int n;//|a| 
char a[N+5];//字符串 
int lcP[N+1],Lcs[N+1];//每个后缀与a的LCP、每个前缀与a的LCS 
int z[N+1];//z数组 
void z_init(){//对a跑Z算法 
	z[1]=n;
	int zl=0,zr=0;
	for(int i=2;i<=n;i++)
		if(zr<i){
			z[i]=0;
			while(i+z[i]<=n&&a[1+z[i]]==a[i+z[i]])z[i]++;
			if(z[i])zl=i,zr=i+z[i]-1;
		}
		else if(i+z[i-zl+1]<=zr)z[i]=z[i-zl+1];
		else{
			z[i]=zr-i+1;
			while(i+z[i]<=n&&a[1+z[i]]==a[i+z[i]])z[i]++;
			zl=i;zr=i+z[i]-1;
		}
}
vector<int> dsr[N+1];//真因数序列 
int main(){
	cin>>a+1;
	n=strlen(a+1);
	bool ok=true;
	for(int i=1;i<n;i++)ok&=a[i]==a[i+1];//a的最小循环节是否为1 
	if(ok)return cout<<n<<"\n1",0;//特判最小循环节为1 
	z_init();
	for(int i=1;i<=n;i++)lcP[i]=z[i];//算lcP 
	reverse(a+1,a+n+1);//令a=a^r以算Lcs 
	z_init();
	for(int i=1;i<=n;i++)Lcs[i]=z[n-i+1];//算Lcs 
	ok=true;
	for(int i=1;i<n;i++)if(n%i==0&&lcP[i+1]==n-i)ok=false;//a是否循环 
	if(ok)return puts("1\n1"),0;//特判不循环 
	puts("2");//一定有分成2段的方式 
	for(int i=1;i<n;i++)for(int j=2*i;j<=n;j+=i)dsr[j].pb(i);//预处理每个数的真因数序列 
	int ans=0;
	for(int i=1;i<n;i++){
		ok=true;
		for(int j=0;j<dsr[i].size();j++)if(lcP[dsr[i][j]+1]>=i-dsr[i][j])ok=false;//判断分成的前缀是否循环 
		for(int j=0;j<dsr[n-i].size();j++)if(Lcs[n-dsr[n-i][j]]>=n-i-dsr[n-i][j])ok=false;//判断分成的后缀是否循环 
		ans+=ok;//如果都不循环，答案+1 
	}
	cout<<ans;
	return 0;
}
```

然鹅我~~们~~是追求完美的OIer~~（咦咋又是这句话/yiw）~~，怎么能止步于这种复杂度泥？~~（话说$\mathrm O(n\ln n)$惹我了么）~~直觉告诉我们有$\mathrm O(n)$算法。不难发现一个性质：若对于某个长度$len$，$a_{1\sim len}$是循环的，那么$len$这个长度对判断前缀循环是完全没有用的，因为任何有循环节$len$的字符串都有$a_{1\sim len}$的每个循环节当循环节。于是我们可以从小到大直接枚举循环节$len$，如果$a_{1\sim len}$是循环的（因为是从小到大枚举的，此时循环性已经确定）就`continue`，否则从$2len$开始往后枚举倍数标记循环前缀。不难发现，$len$所有倍数为长度的前缀的循环性满足单调性，所以可以一不循环就`break`。

我们来分析这样做的时间复杂度。所有尝试标记分为标记成功和标记失败。因为每次一标记失败就`break`，容易得出标记失败的总复杂度为$\mathrm O(n)$。容易发现，若一个字符串是循环的，那么它的所有循环节都是最小循环节的倍数。证明：反证法。若不是，那么可以用前面那一大堆证明中的引理和辗转相除法得出比最小循环节更小的循环节，矛盾。得证。于是显然，每个循环的前缀都仅被它的最小循环节成功标记，因为它的其他循环节都是最小循环节的倍数，以其他循环节为长度的前缀一定循环，根据性质`continue`掉了。所以标记成功的总复杂度为$\mathrm O(n)$。所以总复杂度就是$\mathrm O(n)$了。

后缀判循环类似。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=500000;
int n;//|a| 
char a[N+5];//字符串 
int lcP[N+1],Lcs[N+1];//每个后缀与a的LCP、每个前缀与a的LCS 
int z[N+1];//z数组 
void z_init(){//对a跑Z算法 
	z[1]=n;
	int zl=0,zr=0;
	for(int i=2;i<=n;i++)
		if(zr<i){
			z[i]=0;
			while(i+z[i]<=n&&a[1+z[i]]==a[i+z[i]])z[i]++;
			if(z[i])zl=i,zr=i+z[i]-1;
		}
		else if(i+z[i-zl+1]<=zr)z[i]=z[i-zl+1];
		else{
			z[i]=zr-i+1;
			while(i+z[i]<=n&&a[1+z[i]]==a[i+z[i]])z[i]++;
			zl=i;zr=i+z[i]-1;
		}
}
bool Cyc[N+1],cyC[N+1];//前、后缀循环性 
int main(){
	cin>>a+1;
	n=strlen(a+1);
	bool ok=true;
	for(int i=1;i<n;i++)ok&=a[i]==a[i+1];//a的最小循环节是否为1 
	if(ok)return cout<<n<<"\n1",0;//特判最小循环节为1 
	z_init();
	for(int i=1;i<=n;i++)lcP[i]=z[i];//算lcP 
	reverse(a+1,a+n+1);//令a=a^r以算Lcs 
	z_init();
	for(int i=1;i<=n;i++)Lcs[i]=z[n-i+1];//算Lcs 
	ok=true;
	for(int i=1;i<n;i++)if(n%i==0&&lcP[i+1]==n-i)ok=false;//a是否循环 
	if(ok)return puts("1\n1"),0;//特判不循环 
	puts("2");//一定有分成2段的方式 
	for(int i=1;i<=n;i++){//枚举循环节 
		if(Cyc[i])continue;//如果a[1~i]循环则continue 
		for(int j=2*i;j<=n;j+=i)
			if(lcP[i+1]>=j-i)Cyc[j]=true;//标记循环前缀 
			else break;//一不循环则break 
	}
	for(int i=1;i<=n;i++){//后缀类似 
		if(cyC[n-i+1])continue;
		for(int j=n-2*i+1;j>=1;j-=i)
			if(Lcs[n-i]>=n-j+1-i)cyC[j]=true;
			else break;
	}
	int ans=0;
	for(int i=1;i<n;i++)ans+=!Cyc[i]&&!cyC[i+1];//如果都不循环，答案+1 
	cout<<ans;
	return 0;
}
```

然鹅其实有更简单的方法做到$\mathrm O(n)$，那就是KMP。不难发现，$kmp$数组的定义与字符串判循环的方法高度相似。很容易得出结论：
1. 若$kmp_{x,|x|}=0$，显然$x$不循环；
2. 若$kmp_{x,|x|}\neq0,|x|-kmp_{x,|x|}\mid|x|$，显然$x$循环，且最小循环节为$|x|-kmp_{x,|x|}$；
3. 若$kmp_{x,|x|}\neq0,|x|-kmp_{x,|x|}\nmid|x|$，则$x$不循环。可以把$x$看作一个不完整循环字符串加以证明。

于是跑出$kmp_a,kmp_{a^\mathrm r}$，即可$\mathrm O(1)$判断每个前/后缀是否循环，$lcP,Lcs$什么的都不需要算了。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=500000;
int n;//|a| 
char a[N+5];//字符串 
int kmp[N+1],kmp_r[N+1];//kmp数组 
void kmp_init(int kmp0[]){//对a跑KMP算法 
	for(int i=2;i<=n;i++){
		int now=kmp0[i-1];
		while(now&&a[now+1]!=a[i])now=kmp0[now];
		kmp0[i]=a[now+1]==a[i]?now+1:0;
	}
}
int main(){
	cin>>a+1;
	n=strlen(a+1);
	bool ok=true;
	for(int i=1;i<n;i++)ok&=a[i]==a[i+1];//a的最小循环节是否为1 
	if(ok)return cout<<n<<"\n1",0;//特判最小循环节为1 
	kmp_init(kmp);
	reverse(a+1,a+n+1);//令a=a^r以算kmp_r 
	kmp_init(kmp_r);
	if(!kmp[n]||n%(n-kmp[n]))return puts("1\n1"),0;//特判不循环 
	puts("2");//一定有分成2段的方式 
	int ans=0;
	for(int i=1;i<n;i++)ans+=(!kmp[i]||i%(i-kmp[i]))&&(!kmp_r[n-i]||(n-i)%(n-i-kmp_r[n-i]));//如果都不循环，答案+1
	cout<<ans;
	return 0;
}
```

其实想要AC这题并不难，那些难证的结论也可以感性理解。但是仔细研究起来，这题还是很有价值的，包括了关于字符串循环的几乎所有性质。

~~最后再吐槽一句：为蛤AtCoder就不能像凉心出题人[$\color{black}\mathsf A\color{red}\mathsf{lex\_Wei}$](https://www.luogu.com.cn/user/123294)和[$\color{black}\mathsf E\color{red}\mathsf{T2006}$](https://www.luogu.com.cn/user/115194)一样毒瘤，有$\mathrm O(n)$算法就不给$\mathrm O(n\ln n)$过泥¿¿¿/yiw~~

---

## 作者：1kri (赞：9)

首先特判几种情况：

1. 所有字母全相等，答案二元组显然为 $(n,1)$。
2. 字符串本身就是 $\text{good string}$，答案二元组为 $(1,1)$。

否则可以证明答案为 $2$，因为在 $S$ 最后一个字母前把串割开，前一部分一定不是 $\text{good string}$。

这个结论等价于对于两个不由同一种字母构成的字符串 $S$ 和 $S+c$ （指在 $S$ 后加一任意字母），它们不可能同时为 $\text{good string}$。

考虑反证，假设有最小的 $x$ 满足 $x \in \text{Period}(S+c)$ 且 $x\mid(|S+c|)$，有最小的 $d$ 满足 $d \in \text{Period}(S)$ 且 $d\mid(|S|)$。

则显然有 $x \leq \frac{|S|+1}{2}$，$d \leq \frac{|S|}{2}$，$x\in \text{Period}(S)$。那么 $x+d-\gcd(x,d)\leq |S|$，由 $\text{Periodicity lemma}$ 得 $\gcd(x,d) \in \text{Period}(S)$。

由 $d$ 的最小性可知 $d|x$，故 $d\mid(|S+c|)$，即 $d\mid(|S|+1)$。

又因为字符串不由同一种字母构成，所以 $d>1$，所以 $d$ 不可能同时为 $|S|$ 和 $|S|+1$ 的因数，与原假设矛盾，故原假设不成立，因而结论得证。

知道这个结论后，我们可以枚举每一个分割点，并判断两部分是否为 $\text{good string}$。判断过程可以直接 $\text{kmp}$ 找最小 $\text{Period}$ 并判断是否整除。

时间复杂度：$O(|S|)$ 。

---

## 作者：Prean (赞：7)

诈 骗 题

我一直以为是 DP 什么的有性质，结果发现是道诈骗题，什么性质都没有。

首先特判掉全 $a$ 串。有一个结论：全场最佳只有可能是两个字符串组成的。

随便证明一下。设 $S[i]$ 是长度为 $i$ 的前缀，$T[i]$ 是长度为 $i$ 的后缀。

首先对于 $S[i](2i\geq n)$ 和 $T[i](n\geq 2i-2)$ 的都不用管，这些肯定不是原串的循环。

那么在我们的讨论中，前缀和后缀的长度不可能超过 $n$ 的一半。

找到一个分界点 $i$。如果 $S[i]$ 和 $T[i+1]$ 都是坏的，那么往右或往左移一格一定是好的。

证明：尝试说明若 $S[i]$ 是原串的循环则 $S[i+1]$ 一定不是原串的循环。

首先全 $a$ 串已经被我们判掉了。设一个 $i=ax,i+1=by$。那么 $\gcd(x,y)$ 一定等于 $1$。

若不等于 $1$，那么说明 $\gcd(x,y)\neq 1$，也说明 $\gcd(i,i+1)\neq 1$，而这不可能。

然后，正反跑两遍 KMP 判断是不是循环就完了。。。
```cpp
#include<cstring>
#include<cstdio>
const int M=5e5+5;
int n,F[M],G[M];char s[M],t[M];
inline bool check(){
	for(int i=2;i<=n;++i)if(s[i]!=s[i-1])return false;return true;
}
inline bool check(int*fail,const int&x){
	if(fail[x]*2<x)return true;return x%(x-fail[x]);
}
signed main(){
	int sum(0);
	scanf("%s",s+1);n=strlen(s+1);if(check())return printf("%d\n1",n),0;for(int i=1;i<=n;++i)t[n-i+1]=s[i];
	for(int j=0,i=2;i<=n;++i){
		while(j&&s[i]!=s[j+1])j=F[j];if(s[i]==s[j+1])++j;F[i]=j;
	}
	for(int j=0,i=2;i<=n;++i){
		while(j&&t[i]!=t[j+1])j=G[j];if(t[i]==t[j+1])++j;G[i]=j;
	}
	if(check(F,n))return printf("1\n1"),0;
	for(int i=1;i<n;++i)if(check(F,i)&&check(G,n-i))++sum;printf("2\n%d",sum);
}
```

---

## 作者：wasa855 (赞：6)

这是一篇大炮打蚊子的题解。

观察到字符串是 good 的条件很像 runs，于是先求一个 runs，观察到如果答案不是 1 且不全部相同，那么答案必然是 2，因为最小循环节 $\ge 2$，所以必然存在一种划分方案。

考虑怎么数方案数：

观察到 runs 存在如下性质：

+   每个位置覆盖次数是 $O(\log n)$ 的
+   端点为 $l$ 的 runs 个数为 $O(\log n)$ 个
+   设 $p$ 为 runs 周期，$\sum(len-2p)$ 是 $O(n\log n)$ 的

有了这些性质之后暴力维护即可。

求 runs 可以做到 $O(n)$，于是总复杂度 $O(n)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define Fast_IO ios::sync_with_stdio(false);
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
//mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define fir first
#define sec second
#define mod 998244353
#define B 20041015
#define ll long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
inline int read()
{
	char ch=getchar(); int nega=1; while(!isdigit(ch)) {if(ch=='-') nega=-1; ch=getchar();}
	int ans=0; while(isdigit(ch)) {ans=ans*10+ch-48;ch=getchar();}
	if(nega==-1) return -ans;
	return ans;
}
typedef pair<int,int> pii;
void print(vector<int> x){for(int i=0;i<(int)x.size();i++) printf("%d%c",x[i]," \n"[i==(int)x.size()-1]);}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int add(int x,int y,int z){return add(add(x,y),z);}
inline int sub(int x,int y){return x-y<0?x-y+mod:x-y;}
inline int mul(int x,int y){return 1LL*x*y%mod;}
inline int mul(int x,int y,int z){return mul(mul(x,y),z);}
#define N 500005
struct Runs
{
	int l,r,p;
	Runs(int a=0,int b=0,int c=0){l=a,r=b,p=c;}
	bool operator < (const Runs &x) const {return l==x.l?r<x.r:l<x.l;}
	bool operator == (const Runs &x) const {return l==x.l&&r==x.r&&p==x.p;}
};
vector<Runs> rs;
int pw[N],_h[N];
char t[N]; int s[N],la[N],st[N],tp,n;
inline int gethash(int l,int r) {return sub(_h[r],mul(_h[l-1],pw[r-l+1]));}
int lcs(int a,int b)
{
	if(a>b) swap(a,b);
	if(s[a]!=s[b]) return 0;
	int l=1,r=n-b+1,ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(gethash(a,a+mid-1)==gethash(b,b+mid-1)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;
}
int lcp(int a,int b)
{
	if(a>b) swap(a,b);
	if(s[a]!=s[b]) return 0;
	int l=1,r=a,ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(gethash(a-mid+1,a)==gethash(b-mid+1,b)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;
}
bool cmp(int l1,int r1,int l2,int r2)
{
	int len=lcs(l1,l2);
	if(r1-l1+1<=len||r2-l2+1<=len) return r1-l1<r2-l2;
	else return s[l1+len]<s[l2+len];
}
void getruns()
{
	tp=0;
	for(int i=n;i>=1;i--)
	{
		st[++tp]=i;
		while(tp>=2&&cmp(i,st[tp],st[tp]+1,st[tp-1])) tp--;
		la[i]=st[tp];
	}
	for(int i=1;i<=n;i++)
	{
		int l=i,r=la[i],len=r-l+1;
		int pre=lcp(l-1,r),suf=lcs(l,r+1);
		int L=l-pre,R=r+suf;
		if((R-L+1)/len>=2) rs.eb(L,R,len);
	}
}
int f[N];
vector<int> p1[N],p2[N],s1[N],s2[N];
inline int getpos(int pos,int id) {return (pos-rs[id].l+1+rs[id].p)/rs[id].p;}
inline int getlen(int pos,int id) {return pos-rs[id].l+1;}
inline int getlen2(int pos,int id) {return pos-rs[id].l-rs[id].p-rs[id].p+1;}
void ins(int pos)
{
	for(int id:p1[pos])
	{
		int rk=getpos(pos,id);
		if(rk!=1) s1[id][getlen(pos,id)]=s1[id][getlen(pos,id)-rs[id].p],s2[id][getlen(pos,id)]=s2[id][getlen(pos,id)-rs[id].p];
		if(rk&1) s1[id][getlen(pos,id)]=add(s1[id][getlen(pos,id)],f[pos]);
		else s2[id][getlen(pos,id)]=add(s2[id][getlen(pos,id)],f[pos]);
		// printf("+ %d %d %d %d\n",pos,id,rk,getlen(pos,id));
	}
}
struct Node{int r,len;};
vector<Node> res[N];
int bad1[N],bad2[N];
signed main()
{
	pw[0]=1; for(int i=1;i<N;i++) pw[i]=mul(pw[i-1],B);
	scanf("%s",t+1); n=strlen(t+1);
	for(int i=1;i<=n;i++) s[i]=t[i]-'a';
	for(int i=1;i<=n;i++) _h[i]=add(mul(_h[i-1],B),s[i]);
	getruns();
	for(int i=1;i<=n;i++) s[i]=27-s[i];
	for(int i=1;i<=n;i++) _h[i]=add(mul(_h[i-1],B),s[i]);
	getruns();
	sort(rs.begin(),rs.end()); rs.erase(unique(rs.begin(),rs.end()),rs.end());
	// for(int i=0;i<(int)rs.size();i++) printf("%d %d %d\n",rs[i].l,rs[i].r,rs[i].p);
	Runs all;
	for(auto [l,r,len]:rs) if(l==1&&r==n&&(r-l+1)%len==0) all=(Runs){l,r,len};
	if(all.l!=0&&all.p==1)
	{
		printf("%d\n%d\n",n,1);
		exit(0);
	}
	else if(all.l==0)
	{
		printf("%d\n%d\n",1,1);
		exit(0);
	}
	for(auto [l,r,len]:rs)
	{
		if(l==1)
		{
			for(int j=len*2;j<=r;j+=len) bad1[j]=1;
		}
	}
	for(auto [l,r,len]:rs)
	{
		if(r==n)
		{
			for(int j=n+1-len*2;j>=l;j-=len) bad2[j]=1;
		}
	}
	int ans=0;
	for(int i=1;i<n;i++) if(bad1[i]==0&&bad2[i+1]==0) ans++;
	printf("%d\n%d\n",2,ans);
	return 0;
}
```



---

## 作者：Exp10re (赞：2)

## 解题思路

考虑先找到原串 $S$ 的最短循环节 $C$ 以及其循环次数 $k$，对其进行分类讨论：

- 若 $|C|=1$，则唯一的划分方案是划分为 $|S|$ 个长度为 $1$ 的子串，因为任意长度 $\geq 2$ 的子串都存在长度为 $1$ 的循环节。
- 若 $|C|=|S|$，则 $S$ 本身就是一个好的串，划分个数为 $1$，方案数也为 $1$。
- 否则，将 $S$ 划分为 $S_1$ 以及 $S_{2,\cdots,|S|}$ 一定 $^\dagger$ 是合法的划分，故划分个数一定为 $2$，我们对于每一个 $i\in[1,n-1]$ 判断 $S_{1,\cdots,i}$ 以及 $S_{i+1,\cdots,n}$ 是否是好的串即可，对其计数得到答案。

$\dagger$：证明：显然 $S_1$ 是好的串，仅需要考虑 $S_{2,\cdots,|S|}$ 是否为好的串即可，记 $T=S_{2,\cdots,|S|}$，设其最短且出现次数 $\geq 2$ 的循环节存在，记为 $P$，则有 $|C|$ 为 $T$ 的**周期**，根据弱周期引理可知 $\gcd(|C|,|P|)$ 也为 $T$ 的周期，而 $\gcd(|C|,|P|) \mid (|P|)$ 可知 $T$ 存在长为 $\gcd(|C|,|P|)$ 的循环节，若 $\gcd(|C|,|P|)\leq |P|$ 则与 $P$ 为最短的循环节矛盾，否则有 $\gcd(|C|,|P|)=|P|$，显然有 $|C|\ne |P|$，由此可知 $S$ 存在长为 $\gcd(|C|,|P|)$ 的循环节，与 $C$ 为 $S$ 最短的循环节矛盾，由此可得 $P$ 不存在，$T$ 为好的串得证。

判断循环节可以枚举循环节长度，用字符串哈希处理并计算每个前缀以及后缀的最短循环节，时间复杂度 $O(n\log n)$。

[这里提供一个实现。](https://atcoder.jp/contests/arc060/submissions/59250744)

---

## 作者：crashed (赞：2)

# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/AT2040)看题目。  
# 分析
&emsp;&emsp;由于 KMP 的失配数组有着天然的找循环节的功能，因此我们不难想到对原串进行两次 KMP ，一正一反。  
&emsp;&emsp;可以发现如下的规律：  
&emsp;&emsp;1. 原串无循环节，这个时候 " 全场最佳 " 只会有一个元素，并且只有一个（即原串本身）；  
&emsp;&emsp;2. 原串存在循环节，并且**仅由一个字符循环而成**，此时唯一的 " 亮眼表现 " 就是将原串拆分成字符；  
&emsp;&emsp;3. 原串存在循环节。可以发现， " 全场最佳 " 只会有两个元素（在一个循环内部进行划分）。我们只需要统计一下划分方式。可以发现，划分方案不会超过$|S|-1$个（$\bmod 10^9+7$都是骗人的）。我们枚举一下划分位置，并检查一下划分出来的两段有没有循环节即可。（不能直接算 qwq ， WA 哭了......）  
&emsp;&emsp;时间是$O(|S|)$。  
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 5e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

char S[MAXN];
int nxt1[MAXN], nxt2[MAXN];
int N;

void calc( int *ret )
{
	ret[1] = 0;
	for( int i = 2, j = ret[1] ; i <= N ; i ++ )
	{
		while( j && S[i] ^ S[j + 1] ) j = ret[j];
		if( S[j + 1] == S[i] ) j ++;
		ret[i] = j;
	}
}

bool chkPre( const int p ) { return nxt1[p] && p % ( p - nxt1[p] ) == 0; }
bool chkSuf( const int p ) { return nxt2[p] && p % ( p - nxt2[p] ) == 0; }
bool chk( const int p ) { return chkPre( p ) == 0 && chkSuf( N - p ) == 0; }

int main()
{
	scanf( "%s", S + 1 );
	N = strlen( S + 1 );
	calc( nxt1 ), std :: reverse( S + 1, S + 1 + N ), calc( nxt2 );
	if( nxt1[N] && N % ( N - nxt1[N] ) == 0 )
	{
		if( nxt1[N] == N - 1 ) { printf( "%d\n%d\n", N, 1 ); return 0; }
		puts( "2" ); int ans = 0;
		for( int i = 1 ; i < N ; i ++ ) 
			ans += chk( i );
		write( ans ), putchar( '\n' );
	}
	else puts( "1\n1" );
	return 0;
}
```    

---

## 作者：良心WA题人 (赞：1)

首先可以简便计算一段字符串是否是好的，直接一个 KMP 即可求出 border，经典结论是长度减去 border 就是最短循环节，而所有的循环节都是最短循环节的倍数，所以只需要判断最短循环节是不是这段字符串的长度的因数即可。

但是发现这样就没法做了。考虑发现一点性质，注意到除了全相同的情况下，一个长度为质数的字符串不会有循环节。根据哥德巴赫猜想，这启发我们或许拆分的个数不会很多。

首先判掉全相同的情况。考虑拆成长度为 $1$ 或 $2$ 的前缀时，这段前缀一定是好的，所以要满足无法拆分就要保证剩余的一定不是好的。而一个长度为 $n$ 的字符串的最小循环节为 $x$ 时，所有循环节长度为 $k\times x$，则所有前缀等于后缀的子串的长度为 $n-k\times x$，在加上一个字符之后前缀等于后缀的子串长度属于 $n-k\times x+1$，则循环节长度属于 $k\times x$，而 $\gcd(n,n+1)=1$，所以 $x$ 在不为 $1$ 时不同时为二者的循环节。故剩下的情况只有一个字符加上剩下的全部相同的可能。注意到此时原串为好串，所以得证。

那么，直接使用 kmp 求出每个前缀和后缀的 border，再统计一下是否合法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=5e5+4;
int ne1[NN],ne2[NN];
char s[NN];
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=2,j=0;i<=n;i++)
	{
		while(j&&s[i]!=s[j+1])
			j=ne1[j];
		if(s[i]==s[j+1])
			j++;
		ne1[i]=j;
	}
	reverse(s+1,s+1+n);
	for(int i=2,j=0;i<=n;i++)
	{
		while(j&&s[i]!=s[j+1])
			j=ne2[j];
		if(s[i]==s[j+1])
			j++;
		ne2[i]=j;
	}
	if(!ne1[n]||n%(n-ne1[n]))
	{
		printf("1\n1");
		return 0;
	}
	int cnt=0;
	for(int i=1;i<n;i++)
		if((!ne1[i]||i%(i-ne1[i]))&&(!ne2[n-i]||(n-i)%(n-i-ne2[n-i])))
			cnt++;
	if(!cnt)
		printf("%d\n1",n);
	else
		printf("2\n%d",cnt);
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

顶级诈骗题。

设字符串 $s$ 的长度为 $n$。

首先需要知道一个字符串是否有循环节。对于串 $s$，它的 **周期** $p$ 需要满足 $\forall i\in [1,n-p],s_i=s_{i+p}$。

- **引理 1**：$s$ 的最小周期为 $n$ 减去它最长 border 的长度。

根据 border 的定义，设 $s$ 有一个长度为 $k$ 的 border，那么子串 $s[1\dots k]$ 与 $s[n-k+1\dots n]$ 就是相同的。更进一步，$s_1=s_{n-k+1},s_2=s_{n-k+2},\cdots,s_k=s_n$。这就是说，$n-k$ 是 $s$ 的一个周期。反过来也是一样。

那么，一个 border 就对应着一个周期，最长的 border 就对应着最短的周期。证毕。

- **引理 2**：如果一个字符串满足它的最小周期 $p\mid n$，那么它存在循环节，并且最短循环节为 $p$。

显然循环节是一个周期。由于一个字符串相当于循环节重复若干次，那么循环节的长度也要是字符串长度的约数。最短的周期也对应着最短的循环节。证毕。

现在我们回到题目。分类讨论：

- $s$ 不存在循环节，那么它自己就是全场最佳。
- $s$ 存在长度为 1 的循环节，那只能把字符一个个分开。
- $s$ 存在长度大于 1 的循环节，这个时候只要把第一个字符分开就可以形成一个全场最佳。

但为什么去掉第一个字符后的字符串就没有循环节了呢？

- **引理 3**：若 $p,q$ 为 $s$ 的周期，且 $p+q\le n$，那么 $\gcd(p,q)$ 也是它的周期。（弱周期引理）

不妨令 $p\ge q$。根据周期的定义，对于一个字符 $s_i$，有 $s_{i-p}=s_i=s_{i+q}$，也就是说，$s_{i-p+q}=s_{i}$，又因为 $p+q\le n$，那么 $p-q$ 也为 $s$ 的周期。

根据更相减损法，$\gcd (p,q)$ 也是 $s$ 的周期。证毕。

对于原来的结论，考虑反证法。显然 $p$ 仍然为 $s$ 去掉第一个字符后的周期。假设仍存在一个最小的循环节 $q$，根据循环节的判定，有 $p\le \lfloor \frac{n}{2}\rfloor,q\le \lfloor \frac{n-1}{2}\rfloor$，也就是说，$p+q\le n-1$。

根据弱周期引理，此时 $\gcd(p,q)$ 也为它的周期。根据循环节的判定，它还是一个循环节。

- 如果 $\gcd(p,q)<q$，与 $q$ 为最小循环节的定义矛盾。
- 那么此时 $\gcd(p,q)=q$，也就是 $q\mid p$，此时 $q$ 也必然是原串的循环节，与 $p$ 为原串的最小循环节矛盾。

所以当 $s$ 去掉第一个字符后，就不存在循环节了。

接下来就是计数了。对于循环节大于 1 的情况，我们需要判断从哪些地方切开不存在循环节。

也就是说，如果能从一个位置 $k$ 切开，那么 $s[1\dots k]$ 与 $s[k+1\dots n]$ 均没有循环节。这是一段前缀和一段后缀。

把原串和反串分别做一遍 KMP 即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

int n,nxt[Maxn+5]; char s[Maxn+5];
int chk[Maxn+5];

inline void GetNxt()
{
    nxt[0]=-1;
    For(i,1,n)
    {
        int now=nxt[i-1];
        while(now>=0 && s[now+1]!=s[i]) now=nxt[now];
        nxt[i]=now+1;        
    }
}

int main()
{
    scanf("%s",s+1),n=strlen(s+1);
    GetNxt();
    if(!nxt[n] || n%(n-nxt[n])) {printf("1\n1\n"); return 0;}
    if(n-nxt[n]==1) {printf("%d\n1\n",n); return 0;}
    printf("2\n");
    For(i,1,n) if(!nxt[i] || i%(i-nxt[i])) chk[i]=1;
    reverse(s+1,s+n+1);
    GetNxt();
    int ans=0;
    For(i,1,n) if(!nxt[i] || i%(i-nxt[i])) ans+=(chk[n-i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：1)


博客食用效果更佳：https://www.cnblogs.com/lyttt/p/13906868.html



[题目链接](https://www.luogu.com.cn/problem/AT2040)



#### 题意简述

~~某谷的题意太绕了qwq~~

若一个字符串$s$存在长度小于$|s|$循环节，我们称它是一个好串。

现在要把$s$分割成若干段，要求每一段都是一个好串。

所有满足条件的分割方案中，分割段数最小的那个方案被称为“全场最佳”。

求“全场最佳”的分割段数以及“全场最佳”的方案数。

#### 题目解析

首先考虑怎么把循环节给搞出来。

这个可以用$kmp$的失配数组来做。

如果一个长度为$n$的串$s$由$k$个相同的长度为$len$的子串$t$拼接而成，并且$t$是$s$可以划分的最小循环串，那么一定有$s[1...n-len]=s[len+1...n]$（前$k-1$个子串拼在一起等于后$k-1$个子串拼在一起）

并且根据失配数组（$p[]$）的定义可以知道，$p[n]$就是去掉最后一个$t$的前一个位置。

所以$len=n-p[n]$

那么只需要判断$len|n$就知道是否有循环节了

![](https://img2020.cnblogs.com/blog/1472744/202010/1472744-20201031172847943-847880798.png)





然后考虑这道题。

如果没有循环节，那么很显然答案就是不分割，$1 \  \ \ 1$

如果循环节为$1$，那么就要全部分开 答案就是$\ n \  \ \ 1$

如果有不为$1$的循环节，那么可以从某个循环节的中间断开，分成$2$段。

刚开始还以为可以直接算答案，所以我是这么写的：

```cpp
int k=len/m;
if(k==2) k--;
int ans=len-1-(k-1);
printf("2\n%d\n",ans);
```

然后$WA$掉了才发现有这样的情况：

$aabab\ aabab->aabab\ a\ |\ \ abab$  右边是循环串 

发现总方案数不超过$n-1$（~~所以$1e9+7$是模了个寂寞~~）可以枚举一个断点来看是否满足左右两边都不循环
所以还需要倒着做一遍$kmp$，用之前的方法判断左右两个子串是否为循环串。

由于$t$是最小循环节，所以可以证明至少存在一种方案满足条件（分类讨论循环次数为$2$和大于$2$），所以$2$是最小答案。

还是简单说一下：循环次数为$2$时，从两个循环节之间劈开就可以，因为$t$是最小循环节，所以两个子串一定不循环；循环次数大于$2$时，可以把它分成$2$部分，一段字符串$+1$个字符的形式，那么显然结尾的$1$个字符不循环，接下来证明开头的那一个字符串一定不循环。假设开头的字符串循环，可以画一个图大概看一下，利用两个循环关系对应位置上的数相等，可以导出存在一个更小的循环节，而这与$t$是最小的循环节相矛盾，所以开头的字符一定不循环。

方框是一个循环节，蓝色线段是另外一个循环节（一个是刚开始的，另一个是去掉最后一个字符的循环节）根据对应关系可以得出这些红色的线段都是相等的：

![](https://img2020.cnblogs.com/blog/1472744/202010/1472744-20201031172902673-427486236.png)





然后你发现两条蓝色的线段是相等的，而其中一条蓝色线段有两条红色线段，另一条蓝色线段只有一条红色线段，于是可以对应得到剩下那一部分是红色线段，然后在根据剩下的黑框框相等得到左边那个黑框框的下一部分也是红色线段...然后套娃下去。

并且红色线段的长度是黑框框的长度和蓝色线段长度的因数，所以红色线段一定是一个循环节，所以存在一个更短的循环节，与$t$是最小的循环节相矛盾。



updated:

然后路过的大佬给了我一个数学上的思路：~~（果然数学好和数学不好的人的差距就出来了）~~

假设两个循环节的长度分别为$x,y$，那么有$S_i=S_{i+x},\ S_i=S_{i+y}$

组合一下，$S_i=S_{ax+by}$,$b$可以取一切整数（包括负数，相当于线性组合）

那么$S_i=S_{gcd(x,y)}$

而$x≠y$，则$gcd(x,y)≠x,gcd(x,y)≠y$

所以存在一个更小的循环节。



最后我写的时候$kmp$倒过来的时候写掉了一行，（注释里有），改了好久，还是要多谢大佬orz



------

#### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<string>
#include<map>
#include<cmath>
using namespace std;
#define N 500005
#define MOD 1000000007
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48); c=getchar();}
	return f*x;
}
char s[N];
int p[N],q[N];
int j,len;
bool check1(int i)
{
	int t=i-p[i];
	if(i==t||i%t) return 1;
	return 0;
}
bool check2(int i)
{
	int t=q[i]-i;
	if((len-i+1)==t||(len-i+1)%t) return 1;
	return 0;
}
int main()
{
	scanf("%s",s+1);
	p[1]=0;
	j=0,len=strlen(s+1);
	//表示1...j 和 len-j+1...len 可以匹配 
	for(int i=2;i<=len;i++)
	{//求失配数组
		while(j>0&&s[j+1]!=s[i]) j=p[j];
		if(s[j+1]==s[i]) p[i]=j+1;
		else p[i]=0;
		j=p[i];
	}
	j=len+1,q[len]=len+1;
	for(int i=len-1;i>=1;i--)
	{
		//printf("%d\n",i);
		while(j<len+1&&s[j-1]!=s[i]) j=q[j];
		if(s[j-1]==s[i]) q[i]=j-1;
		else q[i]=len+1;//啊 这里打掉了 
		j=q[i];
	}
	
	int m=len-p[len];
	if(m==1)
	{
		printf("%d\n1\n",len);
		return 0;
	}
	if(len%m||len==m)
	{
		puts("1"); puts("1");
		return 0;
	}
	int ans=0;
	for(int i=1;i<=len-1;i++)
		if(check1(i)&&check2(i+1)) ans++;
	printf("2\n%d\n",ans);
    return 0;
}
```

---

## 作者：xtx1092515503 (赞：1)

设这个字符串为$s$，长度为$n$，下标从$0$开始。

首先，如果$s$全都是由同一种字符构成的，那么没得说，答案就是 ```n 1``` 。

如果不是全由同一种字符构成，我们就先找出$s$存不存在循环节。

如果不存在循环节（即它本身就是一个 ```亮眼表现``` ），那还是没得说，答案一定是 ```1 1``` 。

如果上述情况都不符合，即$s$存在一个长度非$1$且非$n$的循环节，那么我们可以证明， ```全场最佳``` 的长度只能为$2$。

证明很简单。如果$n=1$，那肯定都由同一种字符构成，已经特判掉了 ；否则，我们就可以将$s$分成两个串$[0,0]+[1,n-1]$。$[0,0]$肯定不是循环串；而$[1,n-1]$，因为它由一堆循环串加上少了一个字符的循环串构成，而我们已经特判过字符全相同的情况，因此也一定不是循环串。

那么这么证明完后，我们就可以枚举在什么位置把$s$一刀两断，断成两个循环串。这需要我们以较快速度判断循环串。

当仁不让的想法就是哈希。这里贴一个结论：对于一个字符串$[0,n-1]$，$[0,n-l-1]=[l,n-1]$是其存在一个长度为$l$的循环节的充分必要条件。贴一张图就非常显然了：

![](https://cdn.luogu.com.cn/upload/image_hosting/h3b0egnj.png)

那么我们可以预处理每个$x\in[1,n]$的所有不同的质因数。这个个数极少，最多只有$6$个（$2*3*5*7*11*13*17>500000$）。

则如果某个长度为$x$的串存在一个循环节，这个循环节重复的次数$k$一定是$x$的质因数，则循环节长度$l=\dfrac{x}{k}$。

通过这个结论判断回文串即可。复杂度约为$O(n\log\log n)$。

莫名其妙WA掉最后两个点死活调不出来的哈希代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n,res,pri[500100],mp[500100];
void ural(){
	for(int i=2;i<=n;i++){
		if(!pri[i])pri[++pri[0]]=i,mp[i]=i;
		for(int j=1;j<=pri[0]&&i*pri[j]<=n;j++){
			pri[i*pri[j]]=true,mp[i*pri[j]]=pri[j];
			if(!(i%pri[j]))break;
		}
	}
}
vector<int>v[500100];
void fact(){
	for(int i=2;i<=n;i++)for(int j=i;j!=1;j/=mp[j])if(v[i].empty()||v[i].back()!=mp[j])v[i].push_back(mp[j]);
}
char s[500100];
ull sd1=998244353,sd2=1000000009,pov1[500100],pov2[500100];
struct HASH{
	ull val1,val2;
	int len;
	HASH(){
		val1=val2=0ull;
		len=0;
	}
	HASH(char ip){
		val1=val2=ip;
		len=1;
	}
	friend HASH operator +(const HASH &x,const HASH &y){
		HASH z;
		z.val1=x.val1*pov1[y.len]+y.val1;
		z.val2=x.val2*pov2[y.len]+y.val2;
		z.len=x.len+y.len;
		return z;
	}
	friend HASH operator -(const HASH &x,const HASH &y){
		HASH z;
		z.val1=x.val1-y.val1*pov1[x.len-y.len];
		z.val2=x.val2-y.val2*pov2[x.len-y.len];
		z.len=x.len-y.len;
		return z;
	}
	friend bool operator ==(const HASH &x,const HASH &y){
		if(x.len!=y.len)return false;
		if(x.val1!=y.val1)return false;
		if(x.val2!=y.val2)return false;
		return true;
	}
}hs[500100];
bool runaround(int l,int r){
	if(l==r)return true;
	for(auto i:v[r-l+1]){
		int j=(r-l+1)/i;
		if((hs[r-j]-hs[l-1])==(hs[r]-hs[l+j-1]))return false;
	}
	return true;
}
bool checkallsame(){
	for(int i=2;i<=n;i++)if(s[i]!=s[1])return true;
	return false;
}
int main(){
	scanf("%s",s+1),n=strlen(s+1),pov1[0]=pov2[0]=1;
	for(int i=1;i<=n;i++)pov1[i]=pov1[i-1]*sd1,pov2[i]=pov2[i-1]*sd2;
	ural(),fact();
//	for(int i=1;i<=n;i++){for(auto j:v[i])printf("%d ",j);puts("");}
	for(int i=1;i<=n;i++)hs[i]=hs[i-1]+HASH(s[i]);
	if(!checkallsame()){printf("%d\n1\n",n);return 0;}
	if(runaround(1,n)){printf("1\n1\n");return 0;}
	printf("2\n");
	for(int i=1;i<n;i++)res+=(runaround(1,i)&&runaround(i+1,n));
	printf("%d\n",res);
	return 0;
}
```
另外还有一种思路，就是通过更加稳定的kmp/Z算法来判断循环串。正经的kmp或Z是不能实现任意地方的循环串判断的；但是这题判断的是前缀/后缀的循环串，因此便没问题了。

Z算法（即扩展KMP）是比较直观的思路，因为$Z$数组的含义就是从当前位置开始的串同字符串前缀的匹配长度。这样，如果有$l+Z[l]\geq x$，则$l$是长度为$x$的前缀的一个循环节长度。

不知道为什么相同的思路哈希没过但Z却过了……玄学的哈希模数~~某$\color{white}\colorbox{white}{长者}$的生日~~也救不了它。

AC的Z代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Z1[500100],Z2[500100],pri[500100],mp[500100],res;
char s[500100];
void Zalgo(int *Z){
	int l=0,r=0;
	for(int i=1;i<n;i++){
		if(i<=r)Z[i]=min(Z[i-l],r-i);
		while(i+Z[i]<n&&s[Z[i]+i]==s[Z[i]])Z[i]++;
		if(i+Z[i]>r)r=i+Z[i],l=i;
	}
}
void ural(){
	for(int i=2;i<=n;i++){
		if(!pri[i])pri[++pri[0]]=i,mp[i]=i;
		for(int j=1;j<=pri[0]&&i*pri[j]<=n;j++){
			pri[i*pri[j]]=true,mp[i*pri[j]]=pri[j];
			if(!(i%pri[j]))break;
		}
	}
}
vector<int>v[500100];
void fact(){
	for(int i=2;i<=n;i++)for(int j=i;j!=1;j/=mp[j])if(v[i].empty()||v[i].back()!=mp[j])v[i].push_back(mp[j]);
}
bool chepre(int x){
	for(auto i:v[x]){
		int j=x/i;
		if(Z1[j]+j>=x)return false;
	}
	return true;
}
bool chesuf(int x){
	x=n-x;
	for(auto i:v[x]){
		int j=x/i;
		if(Z2[j]+j>=x)return false;
	}
	return true;
}
bool checkallsame(){
	for(int i=1;i<n;i++)if(s[i]!=s[0])return true;
	return false;
}
int main(){
	scanf("%s",s),n=strlen(s);
	ural(),fact();
	Zalgo(Z1),reverse(s,s+n),Zalgo(Z2);
	if(!checkallsame()){printf("%d\n1\n",n);return 0;}
	if(chepre(n)){printf("1\n1\n");return 0;}
	puts("2");
	for(int i=1;i<n;i++)res+=(chepre(i)&&chesuf(i));
	printf("%d\n",res);
	return 0;
} 
```


---

## 作者：AZYDLL (赞：0)

本文主要介绍一种字符串 Hash 的做法，结论的证明请参见[这篇题解](https://www.luogu.com.cn/article/y9rqziqw)。这篇文章写的不错，这里就不再赘述了。

# 做法

我们令给定的字符串为 $str$，用二元组 $(a,b)$ 表示第一问的答案为 $a$，第二问的答案为 $b$。

1. 如果 $str$ 本身是一个好串，那么显然它自己就是“全场最佳”，答案为 $(1,1)$。

2. 如果 $str$ 中的每一个元素都相等（如 `aaaaaa`），那么显然能且仅能将字符串分成 $|str|$ 份，答案为 $(|str|,1)$。

3. 否则，根据[这篇题解](https://www.luogu.com.cn/article/y9rqziqw)中证明的结论，我们一定可以将 $str$ 分为两部分。显然分法不超过 $|str|-1$ 种，于是我们枚举断点 $i$，判断 $str_{1 \dots i}$ 与 $str_{i+1 \dots |str|}$ 是否同时为好串即可。统计出方案数 $cnt$，则答案为 $(2,cnt)$。

令 $n=|str|$，时间复杂度为 $O(n \log n)$。

# 复杂度证明

考虑判断一个字符串是否为好串的时间复杂度。容易发现，对于一个字符串 $str$，可以 $O(\log n)$ 求出其最短循环节。若其最短循环节的长度为 $|str|$，则 $str$ 是好串。不会求循环节的话请移步 [P3538](https://www.luogu.com.cn/problem/P3538)。

容易看出，上文的情况 1,2 都可以 $O(\log n)$ 判断。

对于上文中提到的情况 3，单次判断的复杂度是 $O(\log n)$ 的。进行 $n$ 次判断，于是总复杂度就是 $O(n \log n)$。

# 代码


```cpp
#include<bits/stdc++.h>
#define MAXN 500005
#define int long long
#define P 131
#define M 1000000007

using namespace std;
namespace FastIO
{
	inline string _rs()
	{
		string str="";
		int ch=getchar();
		while(ch==' ' || ch=='\n' || ch=='\r') ch=getchar();
		while(ch!=' ' && ch!='\n' && ch!='\r' && ch!=EOF){
			str.push_back(ch);
			ch=getchar();
		}
		return str;
	}
	inline void _ws(string a,char b)
	{
		int len=a.size();
		for(int i=0;i<len;i++) putchar(a[i]);
		putchar(b);
		return ;
	}
	inline int _r()
	{
		int flag=1,ans=0,ch=getchar();
		while((ch<'0' || ch>'9') && ch!=EOF){
			if(ch=='-') flag=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9'){
			ans=(ans<<1)+(ans<<3)+(ch^48);
			ch=getchar();
		}
		return flag*ans;
	}
	inline void _w(int a,char b)
	{
		if(a<0) a=-a,putchar('-');
		int sta[22],top=0;
		do{
			sta[top++]=a%10;
			a/=10;
		}while(a);
		while(top) putchar(sta[--top]+48);
		putchar(b);
		return ;
	}
}
using namespace FastIO;

int len,Hash[MAXN],pw[MAXN],Prime[MAXN],minPrime[MAXN],cnt,cntt;
bool isPrime[MAXN];
string str;

void getPrime()
{
	for(int i=2;i<=len;i++){
		if(!isPrime[i]) Prime[++cnt]=minPrime[i]=i;
		for(int j=1;j<=cnt && i*Prime[j]<=len;j++){
			isPrime[i*Prime[j]]=1;
			minPrime[i*Prime[j]]=Prime[j];
			if(i%Prime[j]==0) break;
		}
	}
	
	return ;
}

bool check(int l,int r)
{
	int len1=r-l+1,len2,ans=r-l+1;
	while(len1>1){
		len2=ans/minPrime[len1];
		len1/=minPrime[len1];
		int hash1=(Hash[r-len2]-(Hash[l-1]*pw[r-l+1-len2])%M+M)%M,hash2=(Hash[r]-(Hash[l+len2-1]*pw[r-l+1-len2])%M+M)%M;
		if(hash1==hash2) ans=len2;
	}
	
	if(ans==r-l+1) return 1;
	return 0;
}

signed main()
{
	str=" "+_rs();
	len=str.size()-1,pw[0]=1;
	for(int i=1;i<=len;i++) Hash[i]=(Hash[i-1]*P+str[i])%M;
	for(int i=1;i<=len;i++) pw[i]=(pw[i-1]*P)%M;
	getPrime();
	
	int flag=1;
	for(int i=1;i<len;i++){
		if(str[i]!=str[i+1]){
			flag=0;
			break;
		}
	}
	if(flag){
		_w(len,'\n'),_w(1,'\n');
		return 0;
	}
	
	if(check(1,len)){
		_w(1,'\n'),_w(1,'\n');
		return 0;
	}
	for(int i=1;i<len;i++) if(check(1,i) && check(i+1,len)) cntt++;
	_w(2,'\n'),_w(cntt,'\n');
	
	return 0;
}
```

---

## 作者：LCat90 (赞：0)

我只会哈希，所以我疯了。

考虑答案可能的情况：

+ $w$ 本身是一个好串。说明它本身就可以当作答案。

+ $w$ 不是一个好串，即有循环节。
	- 循环节为一个字符，只能将 $w$ 分为 $|w|$ 份。
    - 循环节为 $x(x\ge 2)$。容易得出一定可以将其划分为 $2$ 部分使得循环节被打乱。于是枚举分裂点然后 ``check``。
  
如果暴力 ``check``，即枚举循环节长度然后扫一遍判断，有 $71$ 分的好成绩，因为卡满好像是 $O(n\sqrt n\log n)$ 的。

首先我们省略扫一遍的过程，有关键结论：**长度为 $n$ 的字符串 $[1,n]$ 的循环节长为 $l$ 的充要条件是 $[1,n - l]=[l+1,n]$。**

然后我们还要优化暴力枚举循环节（$\sqrt n$ 枚举因数）的过程，考虑预处理出素数，同时将 $x$ 的质数筛过程记录下来，这样我们每次就可以直接分解质因数了。复杂度控制在 $\log n$。

时间复杂度为 $O(n\log n)$，但是常数有点大。

最后，为了防止哈希被卡，我们将模数开到 ``1e18+3`` & 使用 ``__int128``。

```cpp
#include <bits/stdc++.h>
#define int __int128
#define ull unsigned long long
#define pb push_back
using namespace std;
const int N = 5e5 + 5, Mod = (ull)1e18 + 3;;
string s;
int n, pre[N], mul[N], cnt, p[N], mp[N], ans, base = 31;
bool isp[N];
int pp[N], mm[N];
void init() {
    memset(isp, 1, sizeof isp);
	isp[1] = 0;
	for(int i = 2;i <= n; ++i) {
		if(isp[i]) p[++cnt] = i, mp[i] = i;
		for(int j = 1;j <= cnt and p[j] * i <= n; ++j) {
			isp[p[j] * i] = 0, mp[i * p[j]] = p[j];
			if(i % p[j] == 0) break ;
		}
	}
}
vector <int> G[N];
bool pd(int l, int r) { // [1,n - l + 1] = [l,n]
    if(l == r) return 1; int len = r - l + 1;
    for(auto i : G[len]) {
        int j = len / i; 
        if((pp[r - j] - pp[l - 1] * mm[r - l - j + 1] % Mod + Mod) % Mod == (pp[r] - pp[l + j - 1] * mm[r - l - j + 1] % Mod + Mod) % Mod) return 0;
    } 
    return 1;
} 
void write(int x) {
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');    
}
signed main() {	
	cin >> s; 
	n = s.size(); s = ' ' + s;
	mul[0] = mm[0] = 1; init();
    for(int i = 2;i <= n; ++i)  
        for(int j = i;j != 1;j /= mp[j]) 
            if(G[i].empty() or G[i].back() != mp[j]) 
                G[i].pb(mp[j]);
	for(int i = 1;i <= n; ++i) 
        pp[i] = (pp[i - 1] * base + s[i] - 'a') % Mod, mm[i] = mm[i - 1] * base % Mod;
	bool ff = 1; int tmp = n;
	for(int i = 1;i * i <= n; ++i) { // 没有循环节的才直接搞 
		if(n % i) continue ;
		int lst = pp[i]; ff = 1;
		for(int j = 0;j < n;j += i) {
			int x = ((pp[j + i] - pp[j] * mm[i] % Mod) % Mod + Mod) % Mod;
			if(x != lst) { ff = 0; break ; }
		}
		if(ff) {
			tmp = i;
			break ;
		}
		lst = pp[n / i]; ff = 1;
		for(int j = 0;j < n;j += n / i) {
			int x = ((pp[j + n / i] - pp[j] * mm[n / i] % Mod) % Mod + Mod) % Mod;
			if(x != lst) { ff = 0; break ; }
		} if(i == 1) ff = 0;
		if(ff) break ;
	} 
	if(!ff) return puts("1\n1"), 0;
	if(tmp == 1) { write(n); puts("\n1"); return 0;}
	for(int i = 1;i < n; ++i) { // [1,i] + [i + 1,n]
        ans += (pd(1, i) and pd(i + 1, n));
    }
	puts("2"); write(ans);
	return 0;
}
```

---

## 作者：SSER_ZRQ (赞：0)

题目翻译：
- 称一个串 $ S$ 是优的当且仅当它不能被切割成若干个相等的串 $s$。
- 称一个串 $T$ 的最优表达是指把 $T$ 切割成最少的串 $\{S_1,S_2,...S_k\}$，使得每个串 $S_i$ 都是优的。
- 给定串 $T$ ，求：
- 最优表达含多少个串；
- 最优表达有多少种。



------------
#### 题解

设串 $T$ 长度为 $n$ .

首先，如果串 $T$ 只由一个字母组成，那么只能分成 $n$ 段。

其次，如果 $ T $ 没有循环节，则最优表达只含一个串，即串 $T$ 本身。

对于其他情况，最优表达一定只有 $ 2$ 个串，然后枚举 $n-1$ 个可能的断开处，通过 kmp 检查下前缀后缀是否有循环节即可,如果没有，方案+1。

> kmp 关于循环节的结论：如果 $i \bmod (i-nex_i) = 0$，那么 $i-nex_i$ 是前缀 $ i $ 的一个循环节。  
> 事实上，$i-nex_i$ 总是前缀 $ i $ 的一个周期

用 $O(n)$ 时间求出正序（判断前缀）和倒序（判断后缀）kmp，然后用 $O(n)$ 求和。

贴上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
int n,p[N],f[N],ans,v[N];
char s[N],c[N];
int teshu(){
	v[s[1]]++;
	for(int i=2;i<=n;i++){
		if(!v[s[i]]) return 0;
	}
	return 1;
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	if(teshu()){
		printf("%d\n1",n);
		return 0;
	}//判断特殊情况 
	for(int i=2,j=0;i<=n;i++){
		while(j&&s[i]!=s[j+1]) j=p[j];
		if(s[i]==s[j+1]) j++;
		p[i]=j;
	}
	for(int i=1;i<=n;i++) c[i]=s[n-i+1];
	//逆转序列，求倒序kmp 
	for(int i=2,j=0;i<=n;i++){
		while(j&&c[i]!=c[j+1]) j=f[j];
		if(c[i]==c[j+1]) j++;
		f[i]=j;
	}
	if(p[n]==0||n%(n-p[n])!=0){
		printf("1\n1");
		return 0;
	}//情况2，本身就是答案 
	for(int i=1;i<n;i++){ 
		if((p[i]==0||i%(i-p[i])!=0)&&(f[n-i]==0||(n-i)%(n-i-f[n-i])!=0))
			ans++;
		//注意下标问题 
	}
	printf("2\n%d\n",ans);
	return 0;
}

```




---

## 作者：happybob (赞：0)

题意：

给定一个长度为 $n$ 的小写英文字符串 $s$，定义一个字符串 $t$ 是好的，当且仅当其不存在非自身的整周期。你需要将 $s$ 分为若干非空子串使得每部分都是好的。你需要求出最小的分段数量，以及段数等于最小分段数的分段方案数，答案对 $10^9+7$ 取模。

$1 \leq n \leq 5 \times 10^5$，时限 $2$ 秒。

解法：

简单无脑做法是直接 $f_i$ 和 $g_i$ 表示 $[1,i]$ 最小分段数量和方案数，目测不能降低到 $O(n^2)$ 以下，优化前途不是很好。

其实这是一个诈骗题。

下文称非自身整周期为非平凡整周期。

考虑一些简单情况。若 $s$ 所有字符相同，最小分段数量为 $n$，方案数为 $1$。若 $s$ 没有非平凡整周期，最小分段数量为 $1$，方案数也为 $1$。

手玩下其他情况，根据我们敏锐的直觉，我们断言其他情况下最小分段数量为 $2$。此时我们只需要判断每个前缀和后缀是否有非平凡整周期即可。这个直接调和级数哈希是可以的，其次考虑正着和反着 KMP 一次，记 $\pi$ 为 KMP 得到的那个数组。根据下述结论，我们可以得到线性做法。

结论 $1$：

> 一个串有非平凡整周期等价于最小非平凡周期为整周期。

证明：

> 右推左显然，考虑左推右。
>
> 考虑证明逆否命题：如果一个串最小非平凡周期不是整周期，则其必然不存在非平凡整周期。
>
> 假设长度为 $n$ 的字符串 $s$ 有最小非平凡周期 $d \nmid n$，若 $d > \lfloor \dfrac n 2 \rfloor$，显然成立。否则考虑若存在非平凡整周期 $y \mid n$，有 $y \leq \lfloor \dfrac n 2 \rfloor$，则 $d+y \leq n$，根据弱周期引理，存在长度为 $\gcd(d,y)$ 的周期。若 $\gcd(d,y)<d$，与 $d$ 为最小非平凡周期矛盾。若 $\gcd(d,y)=d$，则 $d \mid y$，由于 $d \nmid n$，所以 $y \nmid n$，与假设矛盾，故不存在非平凡整周期。
>
> 证毕。

写一下其实就能过了，问题是为什么答案为 $2$？

事实上，除了特殊情况，有除了 $1$ 的非平凡整周期的字符串，将最后一个字符删去，必然没有非平凡整周期。也就是说，直接将第前 $n-1$ 个字符和最后一个字符分段即可。

结论 $2$：

> 若一个长度为 $n$ 的字符串 $s$ 存在最小非平凡整周期且最小整周期长度大于 $1$，则删去最后一个字符，其必然不存在非平凡整周期。

证明：

> 我们考虑反证。考虑整个字符串 $s$ 有最小非平凡整周期 $x > 1$，假设 $s[1\cdots n-1]$ 有最小非平凡整周期 $y \geq 1$，显然 $x$ 也为 $s[1 \cdots n-1]$ 的一个周期。此外有 $x \leq \lfloor \dfrac{n}{2} \rfloor$ 和 $y \leq \lfloor \dfrac{n-1}{2} \rfloor$，则有 $x+y \leq n - 1$。根据弱周期引理，我们得到 $s[1 \cdots n-1]$ 有一个长度为 $\gcd(x,y)$ 的周期。由于 $y$ 是最小非平凡整周期，$\gcd(x,y)=y$，故 $y \mid x$。由于 $x \mid n$，所以 $y \mid n$。但是 $y$ 又是 $s[1 \cdots n-1]$ 的整周期，所以 $y \mid n-1$，所以 $y=1$，与最小整周期长度大于 $1$ 矛盾。
>
> 证毕。

综上，这种情况下最小分段数量为 $2$，代码很好写，这里就不放了。

---

