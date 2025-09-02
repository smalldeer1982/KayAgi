# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4```

# 题解

## 作者：World_Creater (赞：5)

~~这么有意思的题怎么没人写题解。~~  
本题需要一定的贪心。  
首先我们考虑，如果我们将两次操作合并为一次操作，那么就相当于有两位我们只取反了一次，而剩下几位均取反了两次。**这与直接选择两位取反是等价的。**  
因此我们将题意转化为：你可以花费 $2$ 的代价取反任意两位。  
+ 对于 $k$ 是偶数的情况，显然这个问题跟每次取反一次是等价的，因此我们直接贪心，从左往右扫，将 $0$ 转化成 $1$ 即可。（多出来的操作全部放在最后一位，这样对字典序影响最小）。
+ 对于 $k$ 是奇数的情况，我们可以考虑先将多出来的一次操作处理掉，在转化为 $k$ 是偶数的情况。  
这种情况需要贪心考虑：我们从左往右找到第一个出现的 $1$，并对这一位进行取反。  
这样子我们通过一次操作使得从最高位开始连续的 $1$ 数量最多，不难想到这是字典序最大的方案。  
最后直接按 $k$ 是偶数的情况考虑即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k>>s;
		if(k&1) //对于奇数情况的特殊预处理
		{
			int fi=-1;
			for(int i=0;i<n;i++)
			{
				if(s[i]=='1')
				{
					fi=i;
					ans[i]++;
					k--; 
					break;
				}
			}
			if(fi==-1)
			{
				ans[n-1]++;
				fi=n-1;
				k--;
			}
			for(int i=0;i<n;i++)
			{
				if(i!=fi) s[i]=s[i]=='0'?'1':'0';
			}
		}
		for(int i=0;i<n&&k>0;i++) //贪心将非0位取反
		{
			if(s[i]=='0')
			{
				ans[i]++; 
				k--;
				s[i]='1';
			}
		}
		ans[n-1]+=k; //处理最后1位
		if(k&1)
		{
			s[n-1]=s[n-1]=='0'?'1':'0';
		}
		cout<<s<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<ans[i]<<" ";
			ans[i]=0;
		}
		puts("");
	}
}
```

---

## 作者：Tx_Lcy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1659B)
## 思路
我们从前往后考虑，若这一位是 $1$，且 $k$ 是奇数，显然，这个数会变成相反数，即变为 $0$，这是我们不想看到的，因为字典序是从前往后比较。所以，我们必须消耗一次覆盖把这一位覆盖一次。

同理，当这一位是 $0$，且 $k$ 是偶数，那么我们也必须把这一位覆盖一次。

而如果还有 $k$ 剩余，把它全都加到最后一位，因为前面的不可能去动它，从贪心的角度，最优方案就是加到最后一位。

那么，这题就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e6+10;
int ans[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while (T--){
		int n,k,kk=0;cin>>n>>k;string s;cin>>s;s=" "+s;
		if (!k){
			cout<<s.substr(1,n)<<'\n';
			for (int i=1;i<=n;++i) cout<<"0 ";
			cout<<'\n';continue;
		}
		for (int i=1;i<=n;++i) ans[i]=0;
		for (int i=1;i<n;++i){
		    if (s[i]=='1' && (k&1)) ans[i]=1,++kk;
		    else if (s[i]=='0' && (k&1)) ans[i]=0;
		    else if (s[i]=='0' && k%2==0) ans[i]=1,++kk;
		    else ans[i]=0;
		    if (kk==k) break;
		}
		int la=k-kk;
		ans[n]=la;
		for (int i=1;i<=n;++i)
		    if ((k-ans[i])&1){
		    	if (s[i]=='0') s[i]='1';
		    	else s[i]='0';
			}
		cout<<s.substr(1,n)<<'\n';
		for (int i=1;i<=n;++i) cout<<ans[i]<<' ';
		cout<<'\n';
	}
    return 0;
}
```


---

## 作者：Wsy_flying_forever (赞：2)

## 贪心的好题 

### 补充：此题为 Special Judge

看到此题还没有题解，来补一发。

### 思路： 
题目求 $k$ 次操作后字典序最大的字符串，我们只需观察首位即可。将操作分为两类：改变首位的操作与不改变首位的操作。  
为了让首位为 $1$  

1. 当前位为 $1$，我们当然希望 $k$ 为偶数
2. 当前位为 $0$，我们当然希望 $k$ 为奇数  
  
根据当前 $k$ 的奇偶性花一次或零次操作（让更多的机会去更改后面的数），使当前的 $k$ 满足这一位所对应的上述条件即可。  
**这不就是贪心吗？**  
是的，暴力模拟就能通过本题了。  

### 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch)) {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T,n,k;
int ans[maxn];
char s[maxn];
int main() {
	T=read();
	while (T--) {
		n=read(),k=read();
		scanf("%s",s+1);
		if (k==0) {
			printf("%s\n",s+1);
			while (n--) printf("0 ");
			printf("\n");
			continue;
		}
		bool flag=0;
		int i;
		for (int i=1;i<=n;i++) ans[i]=0;
		for (i=1;i<n;i++) {
			s[i]=((s[i]-48)^flag)+48;
			printf("1");
			if (s[i]==48 && (!(k&1)) || s[i]==49 && (k&1)) {
				k--; flag^=1; ans[i]=1; 
				if (!k) break;
		    }
		}
		if (k) {
			s[n]=(flag^(s[n]-48))+48;
			ans[n]=k;  
			printf("%d",s[n]-48);
		}
		else for (++i;i<=n;i++) printf("%d",flag^(s[i]-48));
		printf("\n");
		for (int i=1;i<=n;i++)
		    printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```
完结撒花！

---

## 作者：Lv_Boxiu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1659B)

这是一道贪心的好题

## 思路

### 字符的变化

我们可以用一个变量记录前面变化的次数，进行变换，公式如下：

```cpp

s[f]=((s[f]-'0')^(l%2))+'0'

```

其中，$s[f]$ 为输入中该位置的字符，$l$ 为前面变换的次数。

### 变化的策略

因为题目要求字典序最大，所以我们应使用贪心，优先保障左侧的字符为 $1$。显然，当 $s[f]=1$ 时，为了保证该位置始终为 $1$ ，剩余变换次数应为偶数，同理，当 $s[f]=0$ 时，为了保证该位置能够变为 $1$，剩余变换次数应为奇数。

### 最后多余的变换次数

因为对于每一个字符而言，留给后面的字符的次数的奇偶性已经决定了它的值，所以我们可以把所有的剩余的次数都给最后一个字符而不对前面的结果造成影响。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans[200005];
int n,k,t,f,l;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>s;
		f=0;                                 //遍历时记录位置
		l=0;                                 //记录已变换次数
		while(f<n-1&&k>0){
		    s[f]=((s[f]-'0')^(l%2))+'0';
		    if(s[f]=='0'&&k%2==0){
		        ans[f]++;
		        l++;
		        k--;
		    }
		    else if(s[f]=='1'&&k%2==1){
		        ans[f]++;
		        l++;
		        k--;
		    }
            s[f]='1';                       //无论如何，这个位置在经过调整后都会一直为1
		    f++;
		}
        while(f<n-1){
	        s[f]=((s[f]-'0')^(l%2))+'0';    //当次数不够时，不再调整，但对后面的字符进行计算
		    f++;
        }
		s[n-1]=((s[n-1]-'0')^(l%2))+'0';    //当次数有剩余时，全部给最后一个字符
        ans[n-1]=k;
		cout<<s<<endl;
		for(int i=0;i<n;i++){
			cout<<ans[i]<<" ";
			ans[i]=0;
		}
        cout<<endl;
	}
    return 0;
}
```

时间复杂度：$O(\sum_{i = 1}^{t} \ {n})$。

（即各组数据中的 $n$ 的总和）

**完结**

---

