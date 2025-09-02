# Lucky PIN

## 题目描述

[problemUrl]: https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_d

AtCoder 社は、オフィスの入り口に $ 3 $ 桁の暗証番号を設定することにしました。

AtCoder 社には $ N $ 桁のラッキーナンバー $ S $ があります。社長の高橋君は、$ S $ から $ N-3 $ 桁を消して残りの $ 3 $ 桁を左から読んだものを暗証番号として設定することにしました。

このとき、設定されうる暗証番号は何種類あるでしょうか？

ただし、ラッキーナンバーや暗証番号はいずれも $ 0 $ から始まっても良いものとします。

## 说明/提示

### 制約

- $ 4\ \leq\ N\ \leq\ 30000 $
- $ S $ は半角数字からなる長さ $ N $ の文字列

### Sample Explanation 1

高橋君には以下の選択肢があります。 - $ S $ の $ 1 $ 桁目を消し、暗証番号を `224` とする。 - $ S $ の $ 2 $ 桁目を消し、暗証番号を `024` とする。 - $ S $ の $ 3 $ 桁目を消し、暗証番号を `024` とする。 - $ S $ の $ 4 $ 桁目を消し、暗証番号を `022` とする。 よって、設定されうる暗証番号は `022`, `024`, `224` の $ 3 $ 種類です。

## 样例 #1

### 输入

```
4
0224```

### 输出

```
3```

## 样例 #2

### 输入

```
6
123123```

### 输出

```
17```

## 样例 #3

### 输入

```
19
3141592653589793238```

### 输出

```
329```

# 题解

## 作者：xxr___ (赞：1)

### 思路：
用三个变量分别记录个位，十位，百位的状态。这里我们贪心的想，百位肯定是越往前选择的机会会越多，所以我们从前往后遍历字符串，每当第一次遇到百位，如果与主函数中的循环中的数的百位一样的话，就将百位的状态标记一下，十位和个位也同理。
### 代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,sum;
string s;
bool check(int x){
	bool flag1=0,flag2=0,flag3=0;
	for(int i=0;i<n;i++){
		if(s[i]==(x/100+'0')&&flag1==0)flag1=1;else if(s[i]==((x/10)%10+'0')&&flag1&&flag2==0)flag2=1;else if(s[i]==(x%10+'0')&&flag2==1)flag3=1;
	}
	return flag3;
}
signed main(){
	cin>>n>>s;
	for(int i=0;i<=999;i++)if(check(i)) sum++;
	cout<<sum;
	return 0;
}
```

---

## 作者：晴空一鹤 (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/AT_sumitb2019_d)

### Solution

容易发现，密码只有 $3$ 位，每位可以为 $0$ ～ $9$ ，总共只有 $1000$ 种可能，所以考虑枚举。

假如我们现在枚举的密码为 $123$ ，首先得找到 $1$ 个 $1$ ，如果序列里有多个 $1$ 我们该选哪一个呢？

选最前面的，因为他在最前面，所以后面可选的数字会是最多的，假如我们选了后面的 $1$ 能选的数字将减少，因此选最前面的一定不劣于选后面的。

于是我们只需对每个位置记录在他之后 $1$ ～ $9$ 第一次出现的位置，再记下整个字符串中 $1$ ～ $9$ 第一次出现的位置，枚举时直接判断即可。

#### CODE

```
#include<bits/stdc++.h>
using namespace std;
int n,f[30005][11],ans;
string s;
int main()
{
   cin>>n>>s;
   for(int i=s.size()-1;i>=0;i--)
   {
     for(int j=0;j<=9;j++)
       f[i+1][j]=f[i+2][j];
       if(i<s.size()-1)
       f[i+1][s[i+1]^48]=i+2;
   }
   for(int i=0;i<=9;i++)
   f[0][i]=f[1][i];
   f[0][s[0]^48]=1;
   for(int i=0;i<=9;i++)
     for(int j=0;j<=9;j++)
       for(int k=0;k<=9;k++)
         if(f[0][i]!=0&&f[f[0][i]][j]!=0&&f[f[f[0][i]][j]][k]!=0)
         ans++;
    cout<<ans<<endl;
}
```


---

## 作者：jiangjiangQwQ (赞：0)

## 思路
分别枚举 $1000$ 种密码，对于每种密码就遍历幸运数字中能否拼成这个密码。时间复杂度就是 $O(1000 \times n)$，可过。主要部分代码：
```cpp
long long n,ans;
string a;
signed main(){
	// fast();
	cin>>n>>a;
	for(int i=0;i<=999;i++){
		string s=to_string(i);
		while(s.size()<3) s="0"+s; 
		int c=0; 
		for(int j=0;j<n;j++) if(a[j]==s[c]) ++c;
		if(c==3) ans++;//,cout<<i<<'\n';
	}
	cout<<ans<<endl;
	return 0;
}
```
似乎换行用转义字符会错。$i$ 为当前所枚举的密码，用 $s$ 将 $i$ 转为字符串，便于比较，$c$ 标记已经匹配的字符数，$ans$ 是最终的答案。

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/AT_sumitb2019_d)

## 题意

给定一个长度为 $N$ 的纯数字字符串，问有多少个三位数是原字符串的 **子序列**。

**注：子序列不连续。**

## 思路

枚举 $0$ 到 $999$，判断是否为原字符串子序列。

## 代码

```cpp
// J2023 | BLuemoon_
#include <bits/stdc++.h>

using namespace std;

int n, f, g, p, ans;
string s;

bool C(int x) {
    f = g = p = 0;
    char h = (x / 100) + '0', t = ((x / 10) % 10) + '0', o = (x % 10) + '0';
	for(int i = 1; i <= n; i++) {
		if (s[i] == h && f == 0) {
            f = 1;
        } else if (s[i] == t && f && g == 0) {
            g = 1;
        } else if (s[i] == o && g) {
            p = 1;
        }
	}
	return p == 1;
}

int main() {
    cin >> n >> s;
    s = ' ' + s;
    for (int i = 0; i <= 999; i++) {
        ans += C(i);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你一个长度为 $n$ 的数字串 $S$，让你在这里面随机保留三位数字，并按它们在原串中的顺序组成一个新的三位数字，问你总共可以组成多少个不同的三位数字？

# 解法分析

首先，我们可以得知这个数一定在 $0$ 到 $999$ 这个区间内，那么我们可以枚举，每一次判断这个数是不是原串的**子序列**。这个应该都会吧？

废话不多说，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans; char c[30005],v[3]; 
inline bool check(){
	int ptr=0;
	for(int i=0;i<n&&ptr<3;++i)
		if(c[i]==v[ptr]) ++ptr;
	return ptr==3;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>c;
	for(int i=0;i<1000;++i){
		v[0]=(i%10)|48;
		v[1]=((i/10)%10)|48;
		v[2]=(i/100)|48;
		ans+=check();
	} 
	cout<<ans<<endl;
	return 0;
}
```

似乎 $O(n)$ 的检查复杂度还直接就最优解榜一了...

---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_sumitb2019_d)

这题难度不大，可以直接枚举。

### 分析

看到这题，我们就可以想到应从 $3$ 位的 PIN 码入手。显然 PIN 码只有 $1000$ 种可能，我们就从 $0$ 到 $999$ 依次枚举。

枚举的过程就相对简单了。把整个字符串遍历一遍，一位一位判断。当三位 PIN 码在字符串中依次存在时这就算一个合法的 PIN 码了。

最后输出合法的 PIN 码的数量。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum;
string s;
bool check(int x){
	bool w1=false,w2=false,w3=false;
	for(int i=0;i<n;++i){
		if(s[i]==char(x/100+48)&&!w1)w1=true;//第一位判断 
		else if(s[i]==char((x/10)%10+48)&&w1&&!w2)w2=true;//第二位判断 
		else if(s[i]==char(x%10+48)&&w2)w3=true;//第三位判断 
	}
	return w3;
}
int main(){
	cin>>n>>s;
	for(int i=0;i<=999;++i)
		if(check(i))
			sum++;//i为合法的PIN码 
	cout<<sum;
	return 0;
}
```
Bye！

---

## 作者：jsisonx (赞：0)

# [题面](https://www.luogu.com.cn/problem/AT_sumitb2019_d)

## 分析
### 题目理解

输入 $n$ 个数，删除其中的 $n-3$ 个数，求有多少种不同的删法。

### 具体分析

删除 $n-3$ 个数，就是保留 $3$ 个数。题目就变成了:$n$ 个数字中包含了多少个不同的三位数。

注意:
包含前导 0 的数也要考虑，比如”024”之类的数也要考虑！

### 具体操作

枚举从“000”开始到“999”，每次枚举先把三位数分成三位（每一位一个一位数），去 $n$ 个数中查询有没有这三个一位数，如果有就答案加一，否则继续枚举。最后输出答案。

 细节：比如数组 0224 中，“020”并不存在。所以要注意顺序，后一位的位置应在前一位之后。

注意输出换行！

# AC 代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int first,second,third;
void decompose(int n){
	first=n/100;
	second=(n%100)/10;
	third=n%10;
}//分解每一位
int search(int n,int lucky[]){
	int findf=0,finds=0,markf,marks;
	for(int k=0;k<n;k++){
		if(lucky[k]==first){
			findf=1;
			markf=k;
			break;
		}
	}
	if(findf==0){
		return 0;
	}
	for(int k=0;k<n;k++){
		if(lucky[k]==second){
			if(k>markf){
				finds=1;
				marks=k;
				break;
			}//判断顺序是否正确，后一位应在前一位的后面位置
            
		}
	}
	if(finds==0){
		return 0;
	}
	for(int k=0;k<n;k++){
		if(lucky[k]==third){
			if(k>marks){
				return 1;
			}
		}
	}
	return 0;
}//查询是否存在
int main(){
	int n,lucky2[30005],ans=0;
	char lucky[30005];
	cin>>n;
	cin>>lucky;
	for(int i=0;i<n;i++){
		lucky2[i]=lucky[i]-'0';
	}
	for(int i=0;i<=999;i++){
		decompose(i);
		if(search(n,lucky2)==1){
			ans++;//存在答案加一
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：_xiaxii (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_sumitb2019_d)

## 题意理解
输入一串数及其长度 $N$，求删除 $N-3$ 个数有多少种不同的结果。

题面看似令人无从下手，但是仔细思考一下就会发现，所谓的删除 $N-3$ 个数，实际上就是在这个数列中**顺着**选出 $3$ 个数。有了这个思路，接下来就好办了。

由于是三个数，所以范围在 $0$ 到 $999$ 之间。只需要判断这 $1000$ 个数是否在数列中出现过就可以了。我们将是否出现的判断封装成一个函数，是返回 $1$，不是返回 $0$，再用一个变量加上它的返回值计数就可以了。

重点讲一下判断函数内。由于数在数列内部是散的，所以就要对数进行拆分。接着再遍历数列中的每一个数，可以用 `flag` 来记录现在正在寻找哪一个数。记得将后一个数的寻找放在前一个数的前面，**不然第一个判断成立之后会直接进入第二个判断**。

### 一些细节
读入的数列是连在一起的，需要作为字符单独读入或者作为字符串整体读入。

还有就是这类题输出最后要换行。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[30001];

int f(int k)
{
	int flag=0;
	int i1=k/100,i2=k/10%10,i3=k%10;//三位数分解
	
	for(int i=1;i<=n;i++)
	{
		if(a[i]==i3&&flag==2)
		{
			return 1;//这里可以直接return 1，不需要全部找完
		}
		
		if(a[i]==i2&&flag==1)
		{
			flag++;
		}
		
		if(a[i]==i1&&flag==0)
		{
			flag++;
		}
		
	}
	return 0;
}

int main()
{
	long long cnt=0;
	
	cin>>n;

	for(int i=1;i<=n;i++)
	{
		char k;
		cin>>k;
		a[i]=k-'0';//char转int
	}
	
	for(int i=0;i<=999;i++)//遍历所有的三位数
	{
		cnt+=f(i);
	}
	
	cout<<cnt<<endl;//记得换行
    
    return 0;
}
```
实测[满分](https://www.luogu.com.cn/record/93142811)。

本[蒟蒻](https://www.luogu.com.cn/user/728002)的第六篇题解。

---

