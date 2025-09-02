# [GCJ 2009 #1C] All Your Base

## 题目描述

公元 2100 年，外星人来到了地球。他们用一种神秘的语言写下了一条信息，并在旁边写下了一串符号。我们推测这些符号表示一个数字：距离战争爆发还有多少秒！

遗憾的是，我们完全不知道每个符号代表什么。我们认为每个符号都代表着一个数字，但我们不确定每个数字的含义，也不清楚外星人用的是什么进制。例如，如果他们写下了 "ab2ac999"，这可能意味着十进制下的 "31536000"——恰好是一年——也可能是六进制下的 "12314555"——也就是 398951 秒，约等于四天半。我们可以确定三件事：这个数字是正数；和我们一样，外星人绝不会让数字以零开头；他们不会使用一进制（即基数为 1）。

你的任务是确定距离战争爆发的最小可能秒数。

## 说明/提示

**限制条件**

- $1 \leq T \leq 100$
- 答案不会超过 $10^{18}$

**小数据集（8 分）**

- 每行长度 $1 \leq \text{长度} < 10$

**大数据集（15 分）**

- 每行长度 $1 \leq \text{长度} < 61$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
11001001
cats
zig```

### 输出

```
Case #1: 201
Case #2: 75
Case #3: 11```

# 题解

## 作者：ouxiyao (赞：3)

[传送门](https://www.luogu.com.cn/problem/P13437)
# P13437 [GCJ 2009 #1C] All Your Base
先填空：十年OI一场空，______________；多测不清空，__________。         
然后开始正题：     
这题题意有些难理解，意思是：将所有相同的字符替换为相同的数，使得所形成的数在最小的进制下最小。                      
那么我们就贪心：位置越靠左，权值就越大，那么我们就要使越左边的位越小，并且不含前导 $0$。                  
先对最高位特殊处理：
```
ls = s.size()-1,q = 1,ans = 0;//位数，权值，答案。
zm[zh(s[0])] = 1;//zm指每个字符代表什么数。特殊处理。
a[0] = 1;//特殊处理。
```
然后开始贪心，用 $lz$ 来枚举用了多少个数： 
```cpp
for(int i = 1;i<=ls;i++){
	t = zh(s[i]);//计算值
	if(zm[t]==-1)zm[t] = ++lz;//没填，填上
	a[i] = zm[t];//赋值，意思是第i位代表什么数
	if(lz==0)lz++;//跳过=1的情况
}
```
然后就可以转十进制了：
```cpp
lz++;//变为进制数
if(lz==0)lz = 2;//特判，避免被形如1111的数据卡掉
for(int i = ls;i>=0;i--){
    ans = ans+q*a[i];//加权
    q*=lz;//权值累乘
}
```
然后就输出。结束。           
完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int zm[100],lz = 0,a[100];
string s;
int zh(char ch){
	if(ch<='9')return (ch-'0');
	else return (ch-'A'+10);
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	int T,t,ls,q,ans;
	cin>>T;
	for(int o = 1;o<=T;o++){
		cin>>s;
		memset(zm,-1,sizeof(zm));
		memset(a,-1,sizeof(a));
		lz = -1;
		ls = s.size()-1,q = 1,ans = 0;
		zm[zh(s[0])] = 1;
		a[0] = 1;
		for(int i = 1;i<=ls;i++){
			t = zh(s[i]);
			if(zm[t]==-1)zm[t] = ++lz;
			a[i] = zm[t];
			if(lz==0)lz++;
		}
		lz++;
		if(lz==0)lz = 2;
		for(int i = ls;i>=0;i--){
			ans = ans+q*a[i];
			q*=lz;
		}
		printf("Case #%lld: %lld\n",o,ans);
	}
	return 0;
}
```

---

## 作者：__CuSO4__ (赞：2)

### 题解

首先，要使这个字符串代表的数最小，肯定要让最高位的数字尽可能的小。

但是题目说了，最高位不能位 $0$，那就让最高位为 $1$，后一个位为 $0$，接下来为 $2,3,4\dots$，依次往后赋值，遇到相同的字符就设为之前字符的值。

我们可以用一个数组记录每个字符对应的值，用变量 $cnt$ 记录当前已经用了多少个不同的数字，依次往后模拟这个过程，最后计算出答案即可。

此外要注意一点（在代码注释中也强调了），进制数不能为 $1$，所以要加一个判断。

### 代码：
``` cpp
#include <bits/stdc++.h>
using namespace std;

int T, n, a[300], b[300];
string s;

int main()
{
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        memset(a, -1, sizeof(a)), memset(b, 0, sizeof(b));
        cin >> s;
        int cnt = 1;
        a[s[0]] = b[0] = 1;
        for (int i = 1; i < s.size(); i++)
        {
            if (a[s[i]] == -1) a[s[i]] = b[i] = cnt==1 ? 0 : cnt, cnt++;
            else b[i] = a[s[i]];
        }
        cnt = max(cnt, 2);//注意，题目说了不会使用1进制
        long long ans = 0, t = 1;
        for (int i = s.size() - 1; i >= 0; i--)
            ans += b[i] * t, t *= cnt;
        printf("Case #%d: %lld\n", k, ans);
    }
    return 0;
}
```

---

## 作者：New_Void (赞：2)

## [P13437 [GCJ 2009 #1C] All Your Base](https://www.luogu.com.cn/problem/P13437)

### 思路

这道题思路十分简单，说是要让输出的十进制最小，那换一种理解就是确定的进制数最小，所以我们可以把输入的字符串去重，因为最小是二进制，所以进制数是去重后的字符串长度和二的最大值，之后我们把每一个字符进行编号，由于不能有前导零，所以从左数第一个字符编号为一，第二个为零，后面的从二开始依次排列。最后我们用霍纳法则直接求出十进制数即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int read(){
    int k=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') k=k*10+c-'0',c=getchar();
    return k*f;
}
int main(){
    int T;
    T=read();
    int idx=1;
    while (T--){
        string s;
        cin>>s;
        set<char> st;
        for (int i=0;i<s.size();i++){
            st.insert(s[i]);
        }
        int n=st.size();
        unsigned long long sum=0;
        int base=max(2,n);
        map<char,int> m;
        int next=0;
        for (auto i:s){
            if (m.find(i)==m.end()){
                if (next==0) m[i]=1;
                else if (next==1) m[i]=0;
                else m[i]=next;
                next++;
            }
        }
        for (char i:s){
            sum=sum*base+m[i];
        }
        cout<<"Case #"<<idx<<": "<<sum<<endl;
        idx++;
    }
    return 0;
}

```

---

## 作者：WsW_ (赞：1)

### 思路
这种找满足某条件的最小数字都比较套路。首先考虑，作为一个人类如何比较两个数字的大小。  

比较两个数字的大小，首先比较位数。但这题进制不确定，所以比较不了位数，所以不管。  
再比较首位，这题首位想填啥都行，那不能填 $0$，肯定填最小的 $1$。再比较第二位，如果第二位上的字符和第一位一样的，那也只能填 $1$；否则第二位也想填啥都行，那肯定填最小的 $0$。以此类推，如果某一位上的字符之前出现过了，那么只能填之前的，否则填剩下的最小数字。假设填出来之后第 $i$ 位的数字为 $a_i$。  
再来考虑进制，假设进制是 $p$，那把这个数字转成十进制的结果就是 $\sum_{i=1}^{n} (a_i\times p^{n-i-1})$。  
显然 $p$ 越小，结果越小，我们就得找到最小的 $p$。但是 $p$ 得大于所有的 $a_i$，所以 $p\gets \max\{a_i\}+1$。  
用了 `map` 做映射。设字符串长度为 $n$，时间复杂度为 $O(Tn\log n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void work(){
	string s; cin>>s;
	map<char,int>mp;
	vector<int>ans;
	int cnt=-1;
	for(auto c:s){
		if(mp.find(c)==mp.end()){
			if(cnt==-1)cnt=1;
			else if(cnt==1)cnt=0;
			else if(cnt==0)cnt=2;
			else ++cnt;
			mp[c]=cnt;
		}
		ans.push_back(mp[c]);
	}
	ll sum=0,p=1;
	for(int i=ans.size()-1;i>=0;--i){
		sum+=ans[i]*p;
		p*=max(2ll,(ll)mp.size());
	}
	cout<<sum<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T; cin>>T;
	for(int i=1;i<=T;i++){
		cout<<"Case #"<<i<<": ";
		work();
	}
	return 0;
}
```

---

## 作者：Clouds_dream (赞：1)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13437)  
将外星人给出的字符串解释为一个数字，我们要确定这个数字的进制和每个字符对应的数字。目标是找到在所有可能的解释中，能够得到的最小正整数值。

### 题目分析
为了最小化数字的值，我们要：

1. **确定进制**：进制的最小可能值等于字符串中不同字符的数量。例如，字符串 `cats` 有 4 个不同字符，因此最小的进制是 4。
2. **分配数字**：为了最小化数字的值，我们要将最小的数字分配给最高权重的字符：
   - 第一个字符（最高位）不能为零，因此分配 1。
   - 第二个不同的字符分配 0。
   - 第三个不同的字符分配 2，依此类推，依次分配剩余的最小数字。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void f(int t){
	string s;
	cin>>s;
	map<char,int>shu;
	int jin=0;
	for(char c:s){//统计不同字符的数量
		if(shu.find(c)==shu.end()){
			shu[c]=-1;//先标记为未分配
			jin++;
		}
	}
    jin=max(jin,2ll);// 确定进制

    // 分配数字
    int nd=0;
    shu[s[0]]=1;//第一个字符分配1
    for(int i=1;i<s.size();i++){
    	if(shu[s[i]]==-1){
    		if(nd==1)nd++;//跳过1，因为1已经被分配
    		shu[s[i]]=nd;
    		nd++;
    		if(nd==1)nd++;//确保1不会分配给其他字符
    	}
    }
    //计算数值
    int ans=0;
    for(char c:s){
        ans=ans*jin+shu[c];
    }
	cout<<"Case #"<<t<<": "<<ans<<endl;
}

signed main()
{
	fst
	int y;
	cin>>y;
	for(int i=1;i<=y;i++){
		f(i);
	}
	return 0;
}
```

---

## 作者：Hkb150429 (赞：0)

## 题意

我读过最绕的题目。

我们认为每个符号都代表着一个数字，但我们不确定每个数字的含义，也不清楚外星人用的是什么进制。例如，如果他们写下了 `ab2ac999`，这可能意味着十进制下的 $31536000$ ——恰好是一年——也可能是六进制下的 $12314555$——也就是 $398951$ 秒，约等于四天半。我们可以确定三件事：这个数字是正数；和我们一样，外星人绝不会让数字以零开头；他们不会使用一进制（即基数为  $1$）。

## 思路

我们先理解题意，现在有一个字符串 $z$，我们要把相同字符替换成相同数字，问换出来的最小值（不同进制）。

首先，我们知道，开头越小，数就越小，但是开头不能为 $0$，所以开头权值为 $1$，第 $2$ 位替换成 $0$，但是不同字符不能重复，所以就替换不同。

然后，我们拼回去，使用[霍纳法](https://www.cnblogs.com/qinduanyinghua/articles/5731534.html)，最后输出就可以了。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i2=1;i2<=t;i2++){
        string z; 
        cin>>z;
        set<char> st;
        for (int i=0;i<z.size();i++){
            st.insert(z[i]);
        }
        int s=st.size();
        int jz=max(2,s);
        map<char,int> m;
        int q=0;
        // 第一个字符不能为0，所以先处理第一个字符
        m[z[0]]=1;
        q++;
        for(int i=1;i<z.size();i++){
            char k=z[i];
            if(m.find(k)==m.end()){
                if(q==1){
                    m[k]=0;
                }else{
                    m[k]=q;
                }
                q++;
            }
        }
        unsigned long long sum=0;
        for(int i=0;i<z.size();i++){
            sum=sum*jz+m[z[i]];
        }
        cout<<"Case #"<<i2<<": "<<sum<<endl;
    }
    return 0;
}
```

---

## 作者：rxr2018360074 (赞：0)

（话说 $23$ 分的题目是什么鬼）

拿到题目，先读懂题意：给一个**只包含小写字母与数字**的字符串，每一个字符都有可能是一个数字，求转成十进制后最小是多少？

那么既然不是一个十进制数，我们先认为它就是十进制数，看看能不能找到规律。

比如 `aba212`，我们来分析一下它能代表的数最小是多少：

我们都知道，在位数相同的情况下，我们会从左往右去比较这一位的大小。那么为了让整个数字尽可能小，首先就要让最高位最小，同时题目说了最高位不为零，所以最高位就是 $1$。

接下来看次高位，显然填入 $0$ 最小。

第三位因为与第一位相同，就不需要考虑，直接填 $1$。

第四位时，因为 $0$ 和 $1$ 已经被用过了，所以填接下来最小的 $2$。

第五位，因为 $0\sim2$ 都被使用了，所以填 $3$。

第六位不考虑，直接填 $2$。

所以最小的数就是 $101232$。

在这个过程中，我们可以发现，为了让整个数尽可能小，就要让越靠前的字符代表的数越小，但第一位又不为零。所以得出结论：

1. 最高位填 $1$。
2. 第一个**与最高位不同**的位置填 $0$。
3. 如果与之前相同，则直接填入之前的数，否则填入最小的未被使用的数。

那么进制呢？

很明显，对于同一个数，进制越小它就越小，所以统计出字符的种类作为进制就可以了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int ji[40];
int hashe[40];
int turn(char d){
	if(d>='0' && d<='9'){
		return d-'0';
	}
	else{
		return d-'a'+10;
	}
}
int main(){
	int t;
	cin>>t;
	int d=1;
	while(t--){
		string a;
		cin>>a;
		memset(ji,0,sizeof(ji));
		memset(hashe,-1,sizeof(hashe));
		int n=a.size();
		ll ans=0;  //十年OI一场空，不开long long_____
		a="#"+a;
		int type=0;
		for(int i=1;i<=n;i++){
			ji[turn(a[i])]++;
			if(ji[turn(a[i])]==1){
				type++;
			}
		}
		int num=1;
		for(int i=1;i<=n;i++){
			if(hashe[turn(a[i])]==-1){
				hashe[turn(a[i])]=num;
				if(num==1){
					num=0;
				}
				else if(num==0){
					num=2;
				}
				else{
					num++;
				}
			}
			ans=ans*type+hashe[turn(a[i])];
		}
		cout<<"Case #"<<d<<": "<<ans<<endl;
		d++;
	} 
	return 0;
}

``````
收工~~~~~~

等等，这真的结束了吗？

如果你真的按照上面的代码去写，你就能得到这个东西：

![](https://cdn.luogu.com.cn/upload/image_hosting/mlbfblmd.png)

那这是为什么呢？

回到题中仔细看，就能发现这么一条信息：“**他们不会使用一进制**”

那如果我给出的都是同一个字符，这份代码就会认为它是一进制，从而出错。所以对 $type=1$ 的情况特判即可。

---

## 作者：TCY1234567 (赞：0)

### 题意

给你一个字符串，将字符串中相同的字符替换为相同的数，使得所形成的数在**最小的进制下**满足最小。

### 题解

考虑贪心。

首先肯定是要让第一位最小，此时整个字符串的权值才有可能最小，然后从左到右，只要这个字符未出现过，就将它赋值，最后转成十进制输出即可。

### 正确代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100],b[105];
int pd(char x)
{
	if(x<='9')
		return (x-'0');
	else 
		return (x-'A'+10);
}
signed main()
{
	int t;
	scanf("%lld",&t);
	for(int i=1;i<=t;j++)
	{
		string s;
		cin>>s;
		memset(a,-1,sizeof(a));
		memset(b,-1,sizeof(b));
		int now = -1,len = s.size()-1;
		b[pd(s[0])] = a[0] = 1;
		for(int j=1;j<=len;j++)
		{
			int qwq = pd(s[j]);
			if(b[qwq]==-1) b[qwq] = ++now;
			a[j] = b[qwq];
			if(now==0) now++;
		}
    //上面这个循环是给每一位赋值
		now++;
		int ans = 0;
		int q = 1;
		if(now==0) now = 2;
    //现在就是 now 进制转 10 进制
		for(int j=len;j>=0;j--)
		{
			ans = ans+q*a[j];
			q*=now;
		}
		printf("case #%lld: %lld\n",i,ans);
	}
}//请不要直接复制粘贴，谢谢
```

---

