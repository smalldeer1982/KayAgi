# 「AWOI Round 2 A」最大和

## 题目描述

给你一个整数 $n$，你需要对这个数进行 $m$ 次操作。其中 $m$ 为当前需要操作的数的位数（默认自然数 $0$ 是一位数），且**可能随着 $n$ 的改变而改变**。

第 $i$ $(1\leqslant i \leqslant m)$ 次操作有以下三种选择：

1. $n\gets n+10^{i-1}$。
2. $n\gets n-10^{i-1}$。
3. $n$ 不变。

要求最大化操作后的各个数位上数字之和。

## 说明/提示

**【样例解释】**
- 对于 $33$，每次操作都选择操作 $1$，得到最大值 $4+4=8$。
- 对于 $2023$，第一、二、四次操作都选择操作 $1$，第三次操作选择操作 $2$，得到 $2+9+3+4 = 18$。
- 对于 $10$，选择操作 $2$，得到 $9$，此时 $m$ 变为 $1$。因为已经操作了一次，所以不再操作。
- 对于 $0$，选择操作 $1$ 即可。

**【数据范围】**

对于 $30\%$ 的数据，$1 \leqslant T 
\leqslant10^4$，$0 \leqslant n \leqslant 10^4$。

对于 $100\%$ 的数据，$1 \leqslant T \leqslant 10^5$，$0 \leqslant n \leqslant 10^9$。

**【工作人员】**

| $\text{Idea}$ | $\text{Data}$ | $\text{Check}$ | $\text{Solution}$ |
| :----------: | :----------: | :----------: | :----------: | 
| [S__X](/user/310466) | [S__X](/user/310466)|  [y_kx_b](/user/592895) | [S__X](/user/310466) | 

## 样例 #1

### 输入

```
4
33
2023
10
0```

### 输出

```
8
18
9
1```

# 题解

## 作者：S__X (赞：15)

### 题目简化

给你一个数，从它的个位到最高位进行操作，对于其每一位，你可以选择让他增加 $1$，减少 $1$（如果当前位是 $0$，减 $1$ 后会退位） 或者不变。

### 分析
要使每一位的总和最大，我们可以对每一位进行判断。

- 如果当前位不是 $0$ 和 $9$，那么显然要加一。如：$12$，最大总和即为每一位加一再相加。

- 如果当前位是 $0$ 就减一。简单证明： $-1$ 后，当前位变成 $9$，下一位因为退位需要 $-1$。这样子总和增加了 $9-1=8$，显然比增加 $1$ 更优。如 $100$，最大总和即为个位减一再相加 $(99)$。当然，如果 $a=0$ 就要特判。

- 当前位上的数值为 $9$ 时，不需要操作，证明平凡，和上面相似。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	while(n--){
		int a,sum=0;
		cin>>a;
		if(a==0) sum=1;//特判
		else {
			while(a!=0){
				if(a%10==0) a-=1;//当前值为0时
				else if(a%10!=9) a+=1;//当前值为1~8时
				//为9时不变
				sum+=(a%10);//加和
				a/=10;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：lichenzhen (赞：6)

## 题目大意
给定一个正整数 $n$，你可以将其每一位进行 $+1,-1$ 或是不变，问对 $n$ 的每一位数字都进行一次操作后，$n$ 的各个数位上数字之和是多少？

## 题目解法
很明显的贪心题，我们要想让各个数位的和最大，也就是让每一位数都尽可能的大（尽可能接近 $9$）。

我们可以分情况讨论：
- 若 $n$ 的某一位为 $0$ 时，此时我们对其进行操作 $2$，让其退位，变为 $9$。
- 若 $n$ 的某一位为 $9$ 时，此时我们进行操作 $3$，不需要变化。
- 若 $n$ 的某一位位于 $1 \sim 8$ 之间，此时我们进行操作 $1$，让其尽可能大。

还要注意特判一下 $0$，因为此时只能进行操作 $1$ 和 操作 $2$，最大就是 $1$。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,T;
    cin>>T;
    while(T--){
        int ans=0;
        cin>>n;
        if(n==0) cout<<"1\n";
        else{
            while(n>0){
                if(n%10==0) n-=1;
                else if(n%10>=1&&n%10<=8) n+=1;
                ans+=n%10;
                n/=10;
            }
            cout<<ans<<endl;
        }
    }
}
```

---

## 作者：LegendaryGrandmaster (赞：4)

如果 $n$ 是 $0$，直接特判输出 $1$。

众多周知有个东西叫做 `to_string()`，可以把数字转换成字符串类型，则 `to_string().size()` 便是这个数字的长度，这样更有助于进行操作，在操作的过程中可以随时改变操作次数。

通过观察发现，可以得出数字的某一位上变化情况：

1. 当该位上数字为 $0$ 时，$n\gets n-10^{i-1}$，即这一位的数字变成 $9$，上一位数字减一，这样便会使得数字各位之和最大化。

2. 当该位上数字为 $9$ 时，不变。其他两组操作都会使数字各位之和变小，显而易见。

3. 否则，$n\gets n+10^{i-1}$，同样显而易见，当前位加一。

------------

最后累加数字各项即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int qmi(int a,int b)
{
    int ans=1;
    while(b){
        if(b&1)ans=ans*a;
        b>>=1;
        a=a*a;
    }
    return ans;	
}
signed main()
{
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(!n){
			cout<<"1\n";
			continue;
		}
		for(int i=1;i<=to_string(n).size();i++){
			if(n%qmi(10,i)/qmi(10,i-1)==0)n-=qmi(10,i-1);
			else if(n%qmi(10,i)/qmi(10,i-1)!=9)n+=qmi(10,i-1);
			//cout<<n<<' ';
		}
		int ans=0;
		while(n){
			ans+=n%10;
			n/=10;
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：Rainbow_Sky (赞：2)

比赛没打，来写一下。

## 思路

### 30分

暴力深搜，也是我一开的写法。每次枚举三种可能即可。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxm=1e5+10;
const int maxn=1e3+10;
const int mod=1e9+7;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int a[maxm],n,p,ans;
int check(int x)
{
	int s=0;
	while(x)
	{
		s+=x%10;
		x/=10;
	}
	return s;
}
void dfs(int l,int x,int k)
{
	if(l==k)
	{
		int ans1=check(x);
		ans=max(ans,ans1);
		return ;
	}
	for(int i=0;i<3;i++)
	{
		if(i==0)
		{
			if(x+pow(10,l)>0)
			dfs(l+1,x+pow(10,l),log10(x+pow(10,l))+1);
			else if(x+pow(10,l)==0)dfs(l+1,0,1);
			else return ;
		}
		if(i==1)
		{
			if(x-pow(10,l)>0)
			dfs(l+1,x-pow(10,l),log10(x-pow(10,l))+1);
			else if(x-pow(10,l)==0)dfs(l+1,0,1);
			else return ;
		}
		if(i==2)
		{
			dfs(l+1,x,k);
		}
	}
}
signed main()
{
	int t=read();
	while(t--)
	{
		ans=0;
		n=read();
		p=1;
		if(n!=0) 
		p=log10(n)+1;
		dfs(0,n,p);
		cout<<ans<<"\n";
	}
	return 0;
}
```

### 100分

考虑 $n+10^{i-1}$，$n-10^{i-1}$ 分别是什么。，其实他们就是在 $n$ 的第 $i$ 位上加一不是么。然后分类讨论。

- $n_i=0$，可以看到的，如果减一，会变成 $9$，更优。
- $n_i=1\sim8$，可以看到的，如果加一，会变成 $n_i+1$，更优。
- $n_i=9$，可以看到的，如果加一或减一，会变成 $0$ 或 $8$，所以不变更优。

代码蛮好写的，不放了（还是深搜难写。

---

## 作者：zct_sky (赞：2)

### Description
-----
给定整数 $n$，可以使该数每一位 $+1,-1$ 或不变（$-1$ 有退位），最终使 $n$ 的数位和最大，并输出这个数位和。
### Solution
-----
![](https://cdn.luogu.com.cn/upload/image_hosting/bu5qvrs7.png)

~~作为赛时首杀来水篇题解。~~

考虑贪心。

遍历 $n$ 的数位。

对于 $n$ 的当前位 $x$：

- 若 $0 < x < 9$，则该位最优为 $+1$。
- 若 $x=9$，则 $+1$ 后会进位变成 $0$，整体贡献少了 $9-1=8$，所以该位最优为不变。
- 若 $x=0$，则 $-1$ 后会退位变成 $9$，整体贡献**至少**多了 $9-1=8$，所以该位最优为 $-1$。

特别的，若 $n=0$，因为无法退位，最优为在个位 $+1$，数位和最大为 $1$。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;
}
int t,n,ans; 
int main(){
	t=read();
	while(t--){
		n=read();
		if(!n)ans=1;
		else ans=0;
		while(n){
			if(n%10==9) ans+=9;
			else if(n%10==0)n--,ans+=9;
			else ans+=n%10+1;
			n/=10;
		}
		printf("%d\n",ans);	
	}

	return 0;
}
```

---

## 作者：zxh923 (赞：2)

# P9538 「AWOI Round 2 A」最大和 题解

[题目传送门](https://www.luogu.com.cn/problem/P9538)

### 思路

对这道题，我们可以进行贪心。尽可能的把最多的数字变成 $9$。

首先，$10$ 变成 $9$ 数字之和是变大的，所以我们可以放心的遇到 $0$ 就进行减法操作。

其次，我们的目的是变为 $9$，所以如果已经是 $9$ 了，不进行操作。

其他情况，我们把这一位加上 $1$ 即可。

很重要的一点是：输入 $0$ 要特判输出 $1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,m,n,cnt,ans,po,k;
int main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		if(n==0){//特判0
			cout<<1<<'\n';
			continue;
		}
		k=n;
		while(k>0){
			if(k%10>=1&&k%10<=8)k+=1;//1-8加上1
			if(k%10==9){//遇到9则不变
				ans+=k%10;k/=10;continue;//跳过
			}
			if(k%10==0)k-=1;//遇到0变成9
			ans+=k%10;
			k/=10;//抹掉最后一位并加进答案
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：_7Mr (赞：2)

# 思路
这题思路还是挺简单的。

当当前数值为 $1$ 到 $8$ 时，直接加上 $1$ 就是当前的最优值。

此时我们考虑两种特殊情况。

> 如果当前是 $9$ 时，最优值就是 $8$。

> 如果当前是 $0$ 时，就是 $9$ 但是后一位就需要 $-1$。

还有一种特殊情况 $n=0$ 时直接输出 $1$ 特判就行了。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
int t,n;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    while(t--){
    	cin>>n;
    	if(n==0){//特判
    		cout<<1<<endl;
    		continue;
		}
		int ans=0;
		while(n){//分成上述的3种情况
			int sum=n%10;
			if(sum!=0 && sum!=9) ans+=sum+1,n/=10;//1~8
			if(sum==0 && n/10!=0) ans+=9,n/=10,n--;//0
			if(sum==9) ans+=sum,n/=10;//9
		}
		cout<<ans<<endl;
	}
    return 0;
}

```

---

## 作者：ChenZQ (赞：1)

其实我们的每一个操作就是给 $n$ 的每一位加一或者减 $1$。

那么考虑以下三种情况：

第一种，$n$ 的第 $i$ 位在 $1$ 到 $8$ 之间。那么答案直接加上一。

第二种，$n$ 的第 $i$ 位为 $9$，那么不操作，因为已经最大了。$10$ 的位数和是小于 $9$ 的。

第三种，$n$ 的第 $i$ 为 $0$ 如果他的下一位也是 $0$，就直接答案加上当前位数的数加一，因为没有数给他退了。否则答案加上九，上一位减一。

那么我们可以一位一位地分解，然后就能通过此题啦。

### AC CODE
```
#include <bits/stdc++.h>
using namespace std;


int main()
{
	int __;
	scanf("%d",&__);
	while(__--)//多组数据。
	{
		int n;
		scanf("%d",&n);
		if(n==0)
		{
			cout<<1<<endl;
			continue;//特判特殊情况。
		}
		int ans=0;
		while(n>0)
		{
			int tt=n%10;
			if(tt>=1 && tt<=8) ans+=tt+1;
			else if(tt==0)
			{
				if(n<10) ans+=tt+1;//如果上一位不为0。
				else ans+=9,n-=10;//因为我们是一位一位的分解，所以将下一位减一其实只要减十就好了。
			}
			else ans+=9;
			n/=10;
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：zwyyy (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/P9538)

## 思路
这道题用贪心的思想就可以解决。

而操作 $1,2,3$ 分别可以看做：
1. $n$ 的第 $i$ 位加一；
2. $n$ 的第 $i$ 位减一；
3. $n$ 不变。

接下来分类讨论。

因为我们是想让 $n$ 的各个数位之和尽可能的大，所以：
1. 当 $n$ 的第 $i$ 位为 $0$ 时：采用第二种操作，使其变为 $9$。注意要借位；
2. 当 $n$ 的第 $i$ 位为 $1 \sim 8$ 时：采用第一种操作，使其增加 $1$；
3. 当 $n$ 的第 $i$ 位为 $9$ 时：采用第三种操作，因为 $9$ 已经是最大的数字了，所以无需更改。

```cpp
#include<bits/stdc++.h>
using namespace std;
char n[1000000005];
int t;
int main(){
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		scanf("%s", n);
		if(n[0] == '0'){
			printf("1\n");
			continue;
		}
		int ans = 0;
		for(int j = int(strlen(n)) - 1; j >= 0; --j){
			if(n[j] == '9'){
				ans += int(n[j] - '0');
			}
			else if(n[j] == '0'){
				if(j == 0 && n[j] == '0')	continue;
				ans += int(n[j] - '0') + 9;
				int xia = j;
				while(n[xia] == '0'){
					--xia;
				}
				--n[xia];
				for(int o = xia + 1; o < j; ++o){
					n[o] = '9';
				}
			}
			else{
				ans += int(n[j] - '0') + 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/121063673)

---

## 作者：Vitamin_B (赞：1)

[题目传送门](/problem/P9538)
# 思路
这题我们可以分情况讨论：
1. 当 $a_i=9$ 时，不变；
1. 当 $a_i=0$ 时且 $i\ne0$ 时，减 $1$；
1. 其它情况，是加 $1$。

# 注意事项
1. 多组数据要清空；
1. 注意退位；
1. 注意第 $0$ 位退位之后就不能重新加 $1$ 了，但是 $a=0$ 的情况还是能加 $1$ 的；
1. 注意要倒着枚举。

# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int t, sum;
string a;
int main () {
	cin >> t;
	while (t --) {
		cin >> a;
		sum = 0; //多组数据要清空
		for (int i = a.size (); -- i;) { //倒着枚举
			if (a[i] < '1') //进位 & a[i]=0 的情况
				a[i] = '9', -- a[i - 1];
			else if (a[i] < '9')
				++ a[i];
			sum += a[i] - '0';
		}
		if (a[0] < '9' && (a[0] > '0' || a.size () < 2))
			++ a[0];
		sum += a[0] - '0';
		cout << sum << '\n';
	}
	return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9538)

下午家里断网了，没来参加比赛。

没想到签到题就坑了我这么久。

### 第一次提交

刚看到题，我想这不就是一个水题吗？

思路就是位数上的数如果是 $0$，肯定将其减去 $1$ 变成 $9$，很明显的变成 $9$ 的贡献比较大啊！其他的直接加上再加 $1$ 不就行了，妥妥的！

WA 代码就不放了……

[警钟长鸣。](https://www.luogu.com.cn/record/121085695)

### 第二次提交

自己构造了一组数据。

```
1
99
```
答案很明显是 $18$， 因为 $9$ 已经最大了，没必要改了，但之前我没有判断，就理所当然的 WA 了。

加个细节就行了！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,sum;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>a;
		int cnt=a,ans=0;;
		if(a==0)
		{
			cout<<1<<endl;continue;
		}
		while(cnt)
		{
			int b=cnt%10;
			if(b==9)ans=ans+b;
			else if(b==0) {ans+=9;cnt-=1;}
			else ans=ans+b+1;	
			cnt/=10;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
### 忠告

CSP 将至，~~虽然这不是 CSP 信心赛，~~大家在考场上要把细节全部想到位，争取拿到一个好成绩！不要像我这样粗心大意爆零！

---

## 作者：Spir1t (赞：1)

### [P9538](https://www.luogu.com.cn/problem/P9538)


------------
作为比赛第一题，不水点怎么能行呢？

这道题题目大意就是给你一个数，让你将它每一位加一或减一或不变使得操作后的各个数位上数字之和最大化。

思路比较好想，$9$ 是个位数中最大的，所以我们要使它的每一位尽可能变成 $9$，有了这个思路后这个题就好办了，我们只需判断当前位如果是 $0$，就让它减一得到 $9$，如果是 $9$ 的话就不变，其余数字加一即可。

代码就不放了。

---

## 作者：unknown_risk (赞：0)

本题思路：当前位是 $9$ 保留不动，若是 $0$ 则退位，当前位变成 $9$，上一位减 $1$，因此数字之和增加了 $8$，其他情况则当前位加 $1$。
### My code
```c
#include<bits/stdc++.h>
using namespace std;
int T,n,ans;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		if(n==0)
		{
			puts("1");
			continue; 
		}
		ans=0;
		while(n>0)
		{
			int x=n%10;
			if(x==9)n/=10;
			else if(x==0)
			{
				x+=9;
			    n/=10;
				n--;
			}
			else x++,n/=10;
			ans+=x;
		}
		cout<<ans<<endl;
	}
}
```



---

## 作者：hjqhs (赞：0)

简化题意：对于一个数每位进行操作，可以 $+1$ 或 $-1$ 或不变，最大化操作结束后数位之和。  
分类讨论：  
记当前位为 $x$。  
$1.$ 当 $1 \le x \le 8$ 时，显然加一是最好的，因为不会发生进位也不会发生退位。  
$2.$ 当 $x = 0$ 时，显然减一是最好的，因为会发生退位，前一位减少了 $1$，但这一位从 $0$ 变成了 $9$，增加了 $8$，总的还是优的。  
$3.$ 当 $x = 9$ 时，无论是减一还是加一都会使答案更劣，故因不变。  
写代码时注意 $0$ 要特判。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		int x,ans=0;cin>>x;
		if(x==0){
			cout<<1<<'\n';
		}else{
			while(x){
				if(x%10!=0&&x%10!=9)x+=1;
				else if(x%10==0)x-=1;
				else ;
				ans+=x%10;
				x/=10;
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：zsh_haha (赞：0)

>Subtask 捆绑有误，当场谢罪。


### 解题思路

我们可以使用**贪心**的方法，因为这里是按十进制位**从低到高**位加减，所以不管是进位还是退位都是影响高位，所以这里按位贪心**没有后效性**，是可行的。

贪心过程就是：在当前位“加一，减一，不变”中选择一个最优解，保存结果，继续看下一位。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int a){//求各位和 
	int sum=0;
	while(a){
		sum+=a%10;
		a/=10;
	}
	return sum;
} 
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int maxn=1,pro=1;//注意这里的 maxn 初始为 1，因为无论是什么数，结果都大于等于 1 
		while(pro<=n){
			int a=f(n+pro),b=f(n-pro),c=f(n);//枚举当前位“加一，减一，不变”的情况 
			if(a>=b&&a>=c){//选最优解 
				n+=pro;
				maxn=a;
			}else if(b>=a&&b>=c){
				n-=pro;
				maxn=b;
			}else{
				maxn=c;
			}
			pro*=10;//看下一位 
		}
		cout<<maxn<<endl;
	}
	return 0;
}
```

---

## 作者：Light_az (赞：0)

简化题意：对于 $n$ 的每一位数字，有 $3$ 种选择：加 $1$ 或 减 $1$ 或不变，同时需要考虑进退位，问对每一位数字都进行一次选择后，各个数位上数字之和的最大值是多少？

说实话，赛时我以为是字符串题目，没写出来后考虑贪心：对于第 $i$ 位一定不会对后面的位数产生影响，除了进退位，但是我们肯定不会选择进位，因为 $9$ 变成 $0$ 只进了 $1$ 位，贡献一共减少了 $8$，而退位的话 $0$ 变成了 $9$，退 $1$ 位，但是贡献增加了 $8$，因此可以忽略进退位产生的影响。

但是当最高位由于退位而变成 $0$ 时我们又应该如何处理？举个例子，当 $n=1000$ 时，如果处理不当会变成 $1999$，我们发现当某位置为 $0$ 并且是最高位时，这位数并不可以进行加 $1$ 操作，因此我们特判掉最高位是 $0$ 的时候的情况，并直接分别模拟 $3$ 种操作带来的变化，每次取最大值，这符合贪心的思想，值得注意的是，由于我们直接模拟，因此不需要考虑如何处理进退位，特别的，当 $n=0$ 时，直接输出 $1$ 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
char s[N];
ll f(ll n){//获取 n 的个数位之和
	ll ans=0;
	while(n){
		ans+=n%10;
		n/=10;
	}
	return ans;
}
ll get(ll n){//获取 n 的位数
	ll cnt=0;
	while(n){
		n/=10;
		cnt++;
	}
	return cnt;
}
ll pw(ll k){//10^k
	ll ans=1;
	while(k--) ans*=10;
	return ans;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		k=get(n);
		if(n==0){//特判
			cout<<1<<"\n";
			continue;
		}
		F(i,1,k){
			if(n<pw(k-1)) break;//指退位情况，如 1000 退位成 999，如果不特判，答案会是 1999
			ll a=f(n+pw(i-1)),b=f(n-pw(i-1)),c=f(n);//记录三种情况的结果
			if(a>b&&a>c) n=n+pw(i-1);
			else if(b>a&&b>c) n=n-pw(i-1);
  			//不变不会产生影响，因此可以省略
		}
		cout<<f(n)<<"\n";//各数位之和
	} 

	return 0;
}


```


---

## 作者：fls233666 (赞：0)

我们采用贪心策略。逐一分析各个数位上数字的情况，分类讨论进行操作。

- 如果这个数位上的数字是 $9$，显然这个位置已经最优了，不必操作。
- 如果这个数位上的数字 $\in [1,8]$，那么让这个数位上的数字增加 $1$ 显然是合理且最优的。
- 如果这个数位上的数字是 $0$，这时候进行减 $1$，这个数位上的数字就会转换为 $9$，显然比进行加 $1$ 操作来得更优。

于是按照上述分类讨论逐一实现代码，这题就过了。

值得提醒的是，**操作的次数 $m$ 可能随着 $n$ 的位数改变而改变。** 具体的，进行减 $1$ 操作时，下一位的退位可能会导致 $n$ 的位数减小，进而减少一次操作次数。但是即使这次操作减少了，按照我们上述的方案，我们得到的还是最优解。

以下是代码部分。


```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,fn,ans;
int test;

int main(){
    ll tmp;
    scanf("%d",&test);
    while(test--){
    
        scanf("%lld",&n);
        if(!n){
            printf("1\n");
            continue;
        }  //0的特判
        
        for(fn=1;fn<=n;fn*=10){
            tmp=(n/fn)%10;  //提取当前位上的数字
            if(tmp==0){
                n-=fn;
            }else if(tmp<9)
                n+=fn;
            //分类讨论进行操作
        }  
        
        ans=0;
        for(fn=1;fn<=n;fn*=10)
            ans+=(n/fn)%10;
        printf("%lld\n",ans);  //统计得到答案并输出
        
    }
    return 0;
}
```


---

## 作者：hh弟中弟 (赞：0)

题目很简单，关键是 $m$ 会随着 $n$ 的位数的改变而改变。

我们可以将 $n$ 的每一位看做字符串的每一个元素，不难发现，$n_i$ 只会对 $n_1$ 到 $n_i$ 产生影响，而对他后面的答案是没有影响的。可以说是一个贪心。

我们只需要分析每一位，如果是 $0$ 就将他和前面的每一个元素变为 $9$，直到这个数的第一位，将这个数的第一位减 $1$，如果第一位为 $0$ 将第一位的下标更新加 $1$。

如果这一位是 $9$ 就不变，如果是其他数，就直接加 $1$ 即可。

处理完这一位后，再加上之前的一位就是这一位的答案。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+48);
}
int dp[15];
int main(){
    int t=read();
    while(t--){
    memset(dp,0,sizeof(dp));
    string s;cin>>s;
    s=' '+s;dp[s.size()]=0;
    int m=s.size()-1,w=1;
    if(m==int(1)&&s==" 0"){cout<<1<<endl;break;}
    for(int i=m;i>=w;--i){
        if(s[i]=='0'){
            for(int j=i;j>=w;--j){
                if(s[j]=='0')s[j]='9';
                else {s[j]-=1;
                if(j==w&&s[j]=='0')w++;
                break;}
            }
        }
        if(s[i]!='9'&&s[i]!='0')s[i]+=1;
        dp[i]+=(s[i]-'0')+dp[i+1];
    }
    cout<<dp[w]<<endl;
    }
    return 0;
}

```


---

