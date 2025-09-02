# Kevin and Binary Strings

## 题目描述

Kevin 在月光河公园的河里发现了一个二进制字符串 $s$，它以 1 开头，并把它交给了你。你的任务是从 $s$ 中选择两个非空子串（允许重叠），以使得它们之间的异或值最大。

对于两个二进制字符串 $a$ 和 $b$，它们的异或结果是将 $a$ 和 $b$ 看作二进制数后，进行按位异或操作 $\oplus$ 所得到的结果，其中最左边的位即为最高位。可以参考[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

你选择的字符串可以包含前导零。

## 说明/提示

在第一个测试用例中，我们可以选择 $s_2 = \texttt{1}$ 和 $s_1 s_2 s_3 = \texttt{111}$，此时 $\texttt{1} \oplus \texttt{111} = \texttt{110}$。可以证明这是可能得到的最大值。此外，选择 $l_1 = 3$，$r_1 = 3$，$l_2 = 1$，$r_2 = 3$ 也是一个有效的解决方案。

在第二个测试用例中，选择 $s_1 s_2 s_3 = \texttt{100}$ 和 $s_1 s_2 s_3 s_4 = \texttt{1000}$，则异或结果为 $\texttt{100} \oplus \texttt{1000} = \texttt{1100}$，也是最大的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
111
1000
10111
11101
1100010001101```

### 输出

```
2 2 1 3
1 3 1 4
1 5 1 4
3 4 1 5
1 13 1 11```

# 题解

## 作者：_Lazy_zhr_ (赞：4)

闲话：多测不清空，爆零两行泪。

---

设给出的字符串长度为 $n$。

容易发现其中一个子串必定是给出的字符串，所以先输出 `1 n`。

先找出第一个 $0$ 所在的位置，并设其为 $i$。若给出的字符串中没有 $0$，直接输出 `1 1` 即可。否则我们会得到一个长度为 $n-i+1$ 子串，我们设其为字符串 $s$，它的长度为 $len$。

我们再在原串中寻找一个长度为 $len$ 子串，用这个子串去和 $s$ 异或，前缀 $1$ 最长的就是答案，输出开头编号和结尾编号即可。

最后，代码如下：

```cpp
string s,f,str[5005];
void solve(){
   	int l=0,r=0,maxn=0;
   	f="";//多测不清空，爆零两行泪。
   	cin>>s;
   	int n=s.size(),len;
   	len=n;
   	s=' '+s;
   	cout<<"1 "<<n<<" ";
   	for(int i=1;i<=n;i++){
   		if(s[i]=='0') break;
   		len--;
   	}
   	if(!len){
   		cout<<"1 1\n";
   		return ;
   	}
   	for(int i=n;i>n-len;i--) f=s[i]+f;
   	f=' '+f;
   	int cnt=n-len+1;
   	for(int i=1;i<=cnt;i++){
   		str[i]=" ";
   		for(int j=i;j-i<len;j++) str[i]+=s[j];
   	}//可以和下面的循环合并
    for(int i=1;i<=cnt;i++){
   		int sum=0;
    	bool x=true;
    	for(int j=1;j<=len;j++){
    		if(str[i][j]==f[j]) x=false;
    		if(x) sum++;
    	}
    	if(sum>maxn){
    		l=i,r=i+len-1;
    		maxn=sum;
    	}
    }
    cout<<l<<" "<<r<<"\n";
}
```

---

## 作者：lailai0916 (赞：4)

## 原题链接

- [洛谷 CF2048C Kevin and Binary Strings](https://www.luogu.com.cn/problem/CF2048C)

## 题意简述

给定一个以 $\texttt{1}$ 开头的 $\texttt{01}$ 字符串 $s$，选取两个子串，使得它们的异或和最大。

## 解题思路

设字符串 $s$ 的长度为 $n$，并定义字符串 $t$ 为字符串 $s$ 的按位取反。

显然，第一个子串应选取整个字符串 $s[0:n-1]$，因为只有这样才能保证第一个位置的 $\texttt{1}$ 在异或操作中发挥最大作用。

接下来的目标是让第二个子串的异或结果尽可能大。为了实现这一点，我们需要找到最右边的一个 $\texttt{0}$，设其位置为 $m$。为了最大化异或结果，我们要将这个 $\texttt{0}$ 变为 $\texttt{1}$，因此我们需要选择一个以 $\texttt{1}$ 开头、长度为 $n-m+1$ 的子串。

将第二个子串的选择转化为在字符串 $t[0, m-1]$ 中匹配字符串 $s[m, m]$。如果能够找到匹配的子串，则继续向右进行匹配，直到无法再找到合适的匹配为止。在每次匹配时，右边的部分也要尽量变为 $\texttt{1}$，即在 $t[0, i-1]$ 匹配 $s[m, i]$，依此类推。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int N=5005;
int nxt[N];
int kmp(string s,string t)
{
	int n=s.size(),m=t.size();
	for(int i=1;i<m;i++)
	{
		int j=nxt[i-1];
		while(j&&t[i]!=t[j])j=nxt[j-1];
		if(t[i]==t[j])j++;
		nxt[i]=j;
	}
	int j=0;
	for(int i=0;i<n;i++)
	{
		while(j&&s[i]!=t[j])j=nxt[j-1];
		if(s[i]==t[j])j++;
		if(j==m)return i-m+1;
	}
	return -1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		string s;
		cin>>s;
		int n=s.size(),m=n-1;
		string t=s;
		for(int i=n-1;i>=0;i--)
		{
			t[i]='0'+'1'-t[i];
			if(s[i]=='0')m=i;
		}
		int x=0;
		for(int i=m;i<n;i++)
		{
			int k=kmp(t.substr(0,i),s.substr(m,i-m+1));
			if(k==-1)break;
			x=k;
		}
		cout<<1<<' '<<n<<' '<<x+1<<' '<<x+n-m<<'\n';
	}
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2048C)

## statement

给定一个 $01$ 串，从中选出两个子串 $A$ 和 $B$，使得 $A \oplus B$ 最大的两个选取区间。

## Solution

不难发现，要使两子串异或值最大，其中一个必定原串，这是因为根据题意分析可以得到，在选取的串的长度越长时，最终的异或值一定更大，所以我们固定一个串为原串，暴力从高位去找前缀 $1$ 最多到哪里，然后就是暴力 $O(n ^ 2)$ 枚举异或值最大的子串并记录输出即可。

## code

[代码 click here](https://codeforces.com/contest/2048/submission/297374323)

---

## 作者：Little09 (赞：0)

先特判整个串为 $1$ 的情况。

为了最大化两个串的异或和，肯定想要最大化异或和的二进制位数，为了最大化这个位数，$[1,n]$ 必然被选择。假设我们选择的另一个串的首位为 $1$，若不为 $1$ 可以把前导零全部删去。

找到整个串从前往后的第一个 $0$ 的位置，我们必然想让这个位置变为 $1$，而且不让更前面的 $1$ 改变为 $0$。因此，设第一个 $0$ 的位置为 $p$，则另一个串长度为 $n-p+1$。

如果枚举另一个串的开始位置，线性计算两个串的异或和，取最大值即可。复杂度 $O(n^2)$。

观察到另一个串需要满足：长度为 $n-p+1$，第一个字符为 $1$，所以左端点必须 $<p$，也就是说，另一个串的前缀 $1$ 长度可以在 $[1,p-1]$ 之间任意选择。我们希望原串的第一段 $0$ 尽可能被赋值为 $1$，且第一段 $0$ 后面的那个 $1$ 不会被修改成 $0$，假设原串第一段 $0$ 的长度是 $q$，则选择的另一个串的前缀 $1$ 的长度必然为 $\min(p-1,q)$，容易快速定位到起始位置。复杂度 $O(n)$。

原本出的是线性版本的，不过最后由于一些原因削弱为现在这样。

---

## 作者：_lmh_ (赞：0)

令字符串长度为 $n$（感谢 MatrixGroup 提醒）。

注意到首位为 $1$，所以先把 $[1,n]$ 选一次肯定最优。（只有这样可以把从低往高第 $n$ 位变成 $1$）

要选择两个非空的子串，所以全为 $1$ 时必须把最后一位变成 $0$。

否则，找到最高的一个 $0$ 位。因为存在 $1$，所以肯定可以把这个位置变成 $1$；然后考虑选出的这个 $1$，它唯一确定了选出的第二个子串，也唯一确定了异或之后的结果。

维护一个可能的第二个子串的集合，每次按位贪心，时间复杂度 $O(n^2)$。（也就是说，对每个可能的子串考虑异或上它之后这一位的值，尽可能让它取 $1$。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=5007;
ll T,n,fl;
char s[N],t[N];
vector<ll> ans,tmp[2];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>(s+1);n=strlen(s+1);
		fl=0;
		for (int i=1;i<=n;++i){
			t[i]=s[i];
			if (s[i]=='0'&&fl==0) fl=i;
		}
		if (!fl) cout<<"1 1 1 "<<n<<endl;
		else{
			ans.clear();
			for (int i=1;i<=fl;++i) if (s[i]=='1') ans.emplace_back(i);
			for (int i=fl+1;i<=n;++i){
				tmp[0].clear();tmp[1].clear();
				for (auto x:ans) tmp[s[i]^s[x+i-fl]].emplace_back(x);
				if (tmp[1].size()) ans.swap(tmp[1]);
			}
			cout<<1<<' '<<n<<' '<<ans[0]<<' '<<ans[0]+n-fl<<endl;
		}
	}
	return 0;
}
```

---

## 作者：SmartWind (赞：0)

如果要使异或后的数最大，这里我们把这个二进制数看成一个字符串，从高位到低位，先找到第一个为 $0$ 的位置 ${pos}$，设字符串长度为 ${len}$ ，那么需要进行异或的字符串的区间为 ${[pos,len]}$ ，枚举原字符串中每一个长度与需要异或的那个字符串长度相等的串即可，然后根据数位进行比较，具体可以看代码实现。


```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
string s;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>s;
        int len=s.size();
        cout<<1<<" "<<len<<" ";
        for(int i=0;i<len;i++){
            if(s[i]=='0'){
                int pos=-1,ansl=1,ansr=1;
                int len1=len-i;
                for(int j=0;j<len-len1;j++){
                    string str=s.substr(j,len1);
                    for(int k=0;k<len1;k++){
                        if(str[k]==s[i+k]){
                            if(pos<k){ 
                                pos=k;
                                ansl=j+1,ansr=j+len1;
                            }
                            break;
                        } else if(k==len1-1){
                            pos=k;
                            ansl=j+1,ansr=j+len1;
                        }
                    }
                }
                cout<<ansl<<" "<<ansr<<"\n";
                break;
            } else if(i==len-1){
                cout<<1<<" "<<1<<"\n";
            }
        }
    }
    return 0;
}

```

---

