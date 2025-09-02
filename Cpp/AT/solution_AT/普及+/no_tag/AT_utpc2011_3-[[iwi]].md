# [[iwi]]

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_3



# 题解

## 作者：Rigel (赞：13)

## 思路

由于字符串长度在 $15$ 以下，可以暴力枚举每一个字符是否被取到，并检验组成的字符串是否合法。

检验时，先检验字符串正中间是否是 `iwi`，再检验该串是否对称。

对于所有括号，先用 map 存下另一半。

时间复杂度为 $\mathcal{O}(n2^n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 25
using namespace std;
int n,a[maxn],t[maxn],vis[maxn],ans;
map<int,int>mp;
string s;
void dfs(int now,int stp,int m){ // 在 n 个字符中选 m 个
	if(stp>m){
		int mid=(m>>1)+1;
		if(t[mid-1]!='i'||t[mid]!='w'||t[mid+1]!='i')return; // 判断字符串正中间是否是 iwi
		for(int i=1;i<=mid-2;i++){ // 判断字符串是否对称
			if(!mp[t[i]]){if(t[i]!=t[m-i+1])return;} // 若当前字符不是括号，判断另一边的字符与其是否一致
			else{if(mp[t[i]]!=t[m-i+1])return;} // 否则，判断另一边的字符是否是当前字符的另一半
		}
		ans=max(ans,m);
		return;
	}
	for(int i=now;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;
		t[stp]=a[i];
		dfs(i,stp+1,m);
		vis[i]=0;
	}
}
signed main(){
	mp['(']=')',mp[')']='(',mp['[']=']',mp[']']='[',mp['{']='}',mp['}']='{'; // 存括号的另一半
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;i++)a[i]=s[i-1];
	for(int i=3;i<=n;i+=2){ // 可以证明，符合条件的字符串长度为奇数
		memset(vis,0,sizeof(vis));
		dfs(1,1,i);
	}
	printf("%lld\n",ans);
	return 0;
}

---

## 作者：0x3F (赞：5)

乍看上去毫无头绪，于是我闲着无聊点开了原题，里面有一句话：
```
入力の文字列の長さは 15 以下である。
```
发现有以下字眼：
```
文字列
```
```
15 以下
```
翻成中文就是：
```
输入的字符串长度在15以下。
```
所以呢？

所以暴力枚举所有子串，判断一下是否满足条件即可。

枚举时可以使用位运算：

 $n$ 位二进制数的第 $k$ 位为 $0/1$ 代表原字符串的第 $k$ 个字符取或不取。
 
所以就不用打 dfs 了，真香！
 
关于判断对称的方法：~~见 `AT26`~~ 。

时间复杂度： $\Theta(n2^n)$ .

看代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans;
string str;
int len(string str) {

	//判断中间是否是“iwi”
	if (str.size() < 3) return -1;
	if (!(str.size()&1)) return -1;
	if (str[str.size()>>1] != 'w') return -1;
	if (str[(str.size()>>1)+1] != 'i') return -1;
	if (str[(str.size()>>1)-1] != 'i') return -1;
    
	for (int i = 0, j = str.size()-1; i <= j; i++, j--) {
		//判断是否对称
		if (str[i] == 'i' && str[j] == 'i') continue;
		if (str[i] == 'w' && str[j] == 'w') continue;
		if (str[i] == '(' && str[j] == ')') continue;
		if (str[i] == ')' && str[j] == '(') continue;
		if (str[i] == '[' && str[j] == ']') continue;
		if (str[i] == ']' && str[j] == '[') continue;
		if (str[i] == '{' && str[j] == '}') continue;
		if (str[i] == '}' && str[j] == '{') continue;
		return -1;
	}
	return str.size();
}
string sbstr(int k) {
	//求该二进制数所对应的子串
	string ans;
	int cnt = 0;
	while (k) {
		if (k & 1) ans += str[cnt];
		k >>= 1;
		cnt++;
	}
	return ans;
}
int main() {
	cin >> str;
	for (int i = 0; i < (1<<(str.size())); i++) {
		ans = max(ans, len(sbstr(i)));
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Loxilante (赞：2)

这是道搜索题，~~但是因为我太弱了不会写搜索~~，却又不甘心放过这道题，于是我去AtCoder官网看了看数据范围：

制約:
- 入力の文字列の長さは 15 以下である．

翻译成中文：
- 输入字符串的长度为15以下。

---

解法显而易见，穷举字符串所有子序列，判断其中心是不是iwi，再判断它是不是回文，放入Max中打擂台最后求得最大值。

其中，穷举字符串所有子序列可以用2进制实现。

上代码~：
```
#include<iostream>
#include<string>
#define D(x) cout<<"D:"<<#x<<'='<<x<<endl;
using namespace std;
typedef long long ll;
int l;
string str;
inline string _10to2(ll e) // 10进制转2进制 
{
	ll w[20], idx = 0;
	string ans;
	while(e)
		w[idx++] = e%2, e/=2;
	while(idx--)
		ans+=w[idx]+'0'; 
	return ans;
}
inline string make(string e) // 根据2进制得到子序列 
{
	string ans;
	if (l != e.length()) // 特判如果2进制字符串长度不等于输入字符串长短 
		for(int i = e.length(); i < l; i++) // 在开头用0补齐 
			e.insert(0, "0");
	for(int i = 0; i < e.length(); i++)
		if (e[i] == '1') ans+=str[i]; // 得到子序列 
	return ans;
}
inline bool is_pa(string e) // (is_palindrome) 判断字符串是否回文 
{
	for(int i = 0; i <= e.length()/2; i++)
		if ((e[i] == '(' && e[e.length()-i-1] == ')')
		||	(e[i] == ')' && e[e.length()-i-1] == '(')
		||  (e[i] == '[' && e[e.length()-i-1] == ']')
		||  (e[i] == ']' && e[e.length()-i-1] == '[')
		||  (e[i] == '{' && e[e.length()-i-1] == '}')
		||  (e[i] == '}' && e[e.length()-i-1] == '{')) continue;
		else if (e[i] == '(' || e[i] == ')' || e[i] == '[' || e[i] == ']' || e[i] == '{' || e[i] == '}' || e[i] != e[e.length()-i-1]) return 0;
	return 1;
}
int main(void)
{
	int Max = 3; // 题目保证输入中有iwi 所以可以初始化为3 
	cin>>str;
	l = str.length();
	for(int i = 0; i < 1<<l; i++) // 从1枚举到2^L 
	{
		string t = make(_10to2(i)); 
		if (t[t.length()/2-1] != 'i' || t[t.length()/2] != 'w' || t[t.length()/2+1] != 'i') continue; // 判断中间是否为iwi,如果不是直接跳过 
		if (is_pa(t)) Max = max(Max, (int)t.length()); // 判断是否回文再打擂台 
	}
	cout<<Max<<endl; // 要记得换行QWQ
	return ~~(0-0); // 完结撒花~
}
```

---

## 作者：Fubaogege (赞：1)

尽量简单的题解。
#### 做题方法
最简单的题解，往往使用明显的暴力枚举。 

枚举所有的字符串，判断中心是否是 iwi，在判断是否是回文，再求最大值（因为是最长），只要满足条件就行。   

我们可以用二进制实现。  
换言之：  
- 用暴力枚举；  
- 判断 iwi；  
- 判断回文；   
- 求最大值；    

我们可以用自定义函数实现以上功能。  
#### 代码部分
判断 `iwi`。
```c
int pd(string s){//判断iwi 
	int len=s.length();
	if(len<3)return 0;
	if(!(len&1))return 0;
	if(s[len>>1]+1!='i')return 0;
	if(s[len>>1]-1!='i')return 0;
	if(s[len>>1]!='w')return 0;
	return 1;//排除所有不可能，剩下的是可能。 
}
```
判断回文。  
```c
int pd2(string s){//判断是否回文 
    int len=s.length();
	for(int i=0,j=len-1;i<=j;i++,j--){
		if(s[i]=='i'&&s[j]=='i')continue;//满足 
		if(s[i]=='w'&&s[j]=='w')continue;//满足 
		if(s[i]=='('&&s[j]==')')continue;//满足 
		if(s[i]==')'&&s[j]=='(')continue;//满足 
		if(s[i]=='['&&s[j]==']')continue;//满足 
		if(s[i]==']'&&s[j]=='[')continue;//满足 
		if(s[i]=='{'&&s[j]=='}')continue;//满足 
		if(s[i]=='}'&&s[j]=='{')continue;//满足 
		return 0;//剩下的是不可能 
	}
	return len; 
}
```
二进制对应的子串。
```c
int js(int x){
	string s;
	int t=0;
	while(x>0){
		if((x&1)>0)ans=ans+s[t];
		x>>1;t++;
	}
	return ans;
}
```
主函数照搬就行。  
主函数枚举。
```c
	for(int i=0;i<(i<<len);i++){
		//题目思路函数。 
	}
```

---

## 作者：Wf_yjqd (赞：1)

尊重一下好吗？他起码是个绿题。

既然其他题解全都写的 $\operatorname{O}(n\times2^n)$ 的暴力，我就写个区间 dp 吧。

------------

此题其实就是中间三位固定为 `iwi` 的最长回文子序列。

考虑 $dp_{i,j}$ 表示 $l$ 到 $r$ 的最长长度。

如果两端对称，$dp_{i,j}=dp_{i+1,j-1}+2$。

否则，直接空过一个字符，$dp_{i,j}=\max(dp_{i+1,j},dp_{i,j-1})$。

初始化时所有 $dp_{i,j}$ 全清为无穷小，再枚举所有的 `iwi`，将长度设为 $3$ 即可。

总体复杂度 $\operatorname{O}(n^2)$。

------------

注意此题输出必须换行，我也不知道为啥。。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=84;
int n,dp[maxn][maxn];
char s[maxn];
inline bool check(char x,char y){
    if(x==y)
        return x=='i'||x=='w';
    return x=='('&&y==')'||y=='('&&x==')'||x=='['&&y==']'||y=='['&&x==']'||x=='{'&&y=='}'||y=='{'&&x=='}';
}
int main(){
    memset(dp,0x8f,sizeof(dp));
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i+2<=n;i++)
        if(s[i]=='i'&&s[i+1]=='w'&&s[i+2]=='i')
            dp[i][i+2]=3;
    for(int len=4;len<=n;len++){
        for(int l=1,r;l+len-1<=n;l++){
            r=l+len-1;
            dp[l][r]=max(dp[l+1][r],dp[l][r-1]);
            if(check(s[l],s[r]))
                dp[l][r]=max(dp[l][r],dp[l+1][r-1]+2);
        }
    }
    printf("%d Sherry\n",dp[1][n]);
    return 0;
}
```


---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

是绿题吗？呃......

看到数据范围：字符串长度在 $15$ 以下！萌新的想法就是暴力！

可以暴力枚举字符串所有子序列，判断其中心是不是 `iwi`，再判断它是否对称。


### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
string S;
int len, ans;
string sub (int k) {
    string res = "";
    int c = 0;
    while (c < S.size ()) {
        if (k % 2 != 0) res += S[c];
        k /= 2;
        c ++;
    }
    return res;
}
bool check (string s) {
    if (s.size () < 3 || s.size() % 2 == 0 || s[s.size() / 2] != 'w' || s[s.size() / 2 + 1] != 'i' || s[s.size () / 2 - 1] != 'i') return false;
    for (int i = 0, j = s.size () - 1; i <= j; i ++, j --) 
        if(s[i] == '(' && s[j] != ')' || s[i] == ')' && s[j] != '(' || s[i] == '[' && s[j] != ']' || s[i] == ']' && s[j] != '[' || s[i] == '{' && s[j] != '}' || s[i] == '}' && s[j] != '{' || s[i] == 'i' && s[j] != 'i' || s[i] == 'w' && s[j] != 'w') return false;
    return true;
}

int main () {
    cin >> S;
    len = S.size ();
    for (int k = 1; k <= (1 << len) - 1; k ++) {
        string s = sub (k);
        if (check (s)) ans = max (ans, (int) s.size ());
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Chu_awa_xing (赞：0)

### 这题乍一看，这不是 dp 吗？
 
可是，本蒟蒻不会 dp ，所以就直接暴力了。本来没指望过的，结果竟然 AC 了（做完题去看了原题，发现输入的字符串长度不超过 15 ），所以这道题注定是一道水绿。

### 这题用暴力的方法是，枚举这个字符串所有的字串。

## 判断该字符串是否符合以下条件：

`1.中间要有 iwi ,那么这个字串必然长度要大于 3 。`

`2.是对称的，对称是除 iwi 外呈两两一组，所以字串的长度必然是奇数。`

计算符合以上条件的字串的长度，然后就不用多说了吧。

上代码:


```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int L(string s2) {
	if (s2.size()<3) return 0; //如果字串长度小于3 该字串必定不符合题目要求 
	if (s2.size()%2==0) return 0;  
	if (s2[s2.size()/2]!='w'||s2[s2.size()/2+1]!='i'||s2[s2.size()/2-1]!='i') return 0; //判断iwi是否在该字串的中间位置 
	int j=s2.size();
	for (int i=0;i<=j;i++) {//利用双指针来排查该字串是否对称 
		j--;
		if (s2[i]=='i'&&s2[j]=='i')continue;
		if (s2[i]=='w'&&s2[j]=='w')continue;
		if (s2[i]=='('&&s2[j]==')')continue;
		if (s2[i]==')'&&s2[j]=='(')continue;
		if (s2[i]=='['&&s2[j]==']')continue;
		if (s2[i]==']'&&s2[j]=='[')continue;
		if (s2[i]=='{'&&s2[j]=='}')continue;
		if (s2[i]=='}'&&s2[j]=='{')continue;
		return 0;
	}
	return s2.size();
}
string f(int num){ 
	int c=0;
	string a;
	while (num>0) {
		if (num&1) a+=s[c];
		num/=2,c++;
	}
	return a;
}
int main() {
	int ans=0;
	cin>>s;
	for (int i=0;i<(1<<s.size());i++){//枚举所有字串 
		string s2=f(i); 
		ans=max(ans,L(s2)); //不符合条件的字串返回结果为0，自然就不会更新ans的值。只有符合条件的字串才可以更新ans的值 
	}
	cout<<ans<<endl;
	return 0; //结束力
}
```


---

## 作者：COsm0s (赞：0)

## 思路

这题的数据是“输入字符串的长度为 $15$ 以下。”，题目中没有给出，但 AT 里说了。

既然数据那么小，那考虑二进制枚举所有子串，判断一下是否满足条件即可。

枚举时可以使用位运算：

$n$ 位二进制数的第 $i$ 位为 $0$ 或 $1$ 代表字符串的第 $i$ 个字符取或不取。

在 $check$ 函数内我们从 $0$ 一直扫到字符串的中间。判断这两个字符是否：

1. 若相同，不是括号；

2. 是一个匹配括号的两半（与顺序无关）。

复杂度 $O(n \times 2^n)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans;
string str;
int len(string str) {
	int i=-1,j=str.size();
	while(i<=j) {//双指针判断回文 
		i++,j--;
		if (str[i] == 'i' && str[j] == 'i') continue;
		if (str[i] == 'w' && str[j] == 'w') continue;
		if (str[i] == '(' && str[j] == ')') continue;
		if (str[i] == ')' && str[j] == '(') continue;
		if (str[i] == '[' && str[j] == ']') continue;
		if (str[i] == ']' && str[j] == '[') continue;
		if (str[i] == '{' && str[j] == '}') continue;
		if (str[i] == '}' && str[j] == '{') continue;
		return -1;
	}
	return str.size();
}
string check(int k) {
	string ans;
	int cnt = 0;
	while (k) {
		if (k % 2 == 1) ans += str[cnt];
		k >>= 1;
		++ cnt;
	}//数字转二进制字符串 
	return ans;
}
int main() {
	cin >> str;
	for (int i = 0; i < (1 << (str.size())); i ++) {//从0枚举到2^len-1 
		string st=check(i);
		if (st.size() < 3) continue;
		if (st.size() % 2 == 0) continue;
		if (st[st.size() / 2] != 'w') continue;
		if (st[(st.size() / 2)+1] != 'i') continue;
		if (st[(st.size() / 2)-1] != 'i') continue;
		//特判不合法的情况 
		ans = max(ans, len(st));
	}

	cout << ans << endl;//注意回车 
	return 0;
}
```


---

## 作者：zym_LFCOIer (赞：0)

## 背景
本蒟蒻顺着刷AT绿题，于是写了这篇题解。

[传送门（AT原题，日文，想看就看看吧）](https://atcoder.jp/contests/utpc2011/tasks/utpc2011_3?lang=en)

## 题意
给你一个字符串，取其中不一定相连的子序列，使其为**正中间**是`iwi`，两边分别为对称括号的字符串。求这个子串的最长长度。

## 分析
看了看数据范围：没有？？？
瞟了一眼[日文原题](https://atcoder.jp/contests/utpc2011/tasks/utpc2011_3?lang=en)，发现原字符串长度是15以下。那好办了！直接二进制枚举，判断是否符合题意，最后比个$max$即可。

## $Code$ 
```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int ans[2000010];
int tot=0;

int main(){
    ios::sync_with_stdio(false); //加速（CSP禁用）

    cin>>s;
    int n=s.size();
    string tmp="";
    int cnt=0;
    

    for(int i=0;i<(1<<n);i++){ //用一个整数代表二进制状态
        tmp="";
        cnt=0;
        for(int j=0;j<n;j++){
            if(i>>j&1){  //当前位置上二进制位
                tmp+=s.substr(j,1);
                cnt++;
            }
        }
        if(cnt<3) continue; //小于三，舍去
        if(cnt%2==0) continue; //结果必须是奇数
        int mid=(cnt+1)/2-1;
        if(!(tmp[mid-1]=='i'&&tmp[mid]=='w'&&tmp[mid+1]=='i')) continue; //中间不是iwi，舍去

        bool f=true;

        for(int i=0;i<mid-1;i++){
            int j=cnt-i-1; //对称找括号
            char c=tmp[i],d=tmp[j];
            if(c>d) swap(c,d);
            if(!((c=='('&&d==')')||(c=='['&&d==']')||(c=='{'&&d=='}')||\
                 (c==')'&&d=='(')||(c==']'&&d=='[')||(c=='}'&&d=='{'))){
                f=false;
                break;
            }
        }

        if(!(f==true||tmp=="iwi")) //也许要特判吧
            continue;

        ans[++tot]=cnt;
    }

    sort(ans+1,ans+tot+1); //排序，约等于比max，时间复杂度什么的都是浮云
    cout<<ans[tot]<<endl;
    return 0;
}
```

完结撒花！！

✿✿ヽ(°▽°)ノ✿

附上[记录详情](https://www.luogu.com.cn/record/45494125)


---

## 作者：奆奆的蒟蒻 (赞：0)

这里提供一个思路  
先介绍一个知识点：
##    vector  
>- `vector`是向量类型，可以容纳许多类型的数据，因此也被称为容器
>- 可以将`vector`理解为动态数组，是封装好了的类
>- 进行`vector`操作前应添加头文件`#include<vector>`

### 于是，一篇代码就出来了↓
```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;
int to_do(string s,string t)//已知字符串算结果
{
	int n=s.size(),m=t.size();
	vector<int> c(n+1,0);
	for(int i=0;i<m;i++)
	{
		vector<int> newcost(n+1,0);
		for(int j=0;j<n;j++)
		{
			int maxn=max(newc[j],c[j+1]);
			newc[j+1]=max(maxn,c[j]+(t[i]==s[j]));
		}
		c=newc;
	}
	return c[n]*2+3;//数值为2倍加3
}
int main()
{
	string str;
	while(cin>>str)//不断输入数据
	{
		int n=str.size();//size函数
		string a,b;
		for(int i=0;i<n;i++)
		{
			if(str[i]=='i') break;
			a+=str[i];
		}
		for(int i=n-1;i>=0;i--)//判断条件
		{
			if(str[i]=='i') break;
			if(str[i]=='(') b += ')';
			if(str[i]==')') b += '(';
			if(str[i]=='{') b += '}';
			if(str[i]=='}') b += '{';
			if(str[i]=='[') b += ']';
			if(str[i]==']') b += '[';			
		}
		cout<<to_do(a,b)<<endl;//带入就完了(注意AT的题要换行）
	}
	return 0;
}
```
于是，就
$\Large\color{Green}\text{AC}$
了


---

## 作者：oimaster (赞：0)

几乎是最水的一道 Atcoder 绿题。按照题面模拟即可。

解释一下代码中函数：

- `init()`：初始化
- `next()`：生成出下一个由 2 进制生成的字符串，与 Python 中的 `yield` 语句很像。
- `check()`：检测一个字符串是否满足题面要求。

```cpp
#include<iostream>
using namespace std;
string s;
int n;
bool b[20];
void init(){
	cin>>s;
	s=" "+s;
	n=s.size()-1;
}
string next(){
	int j=n;
	while(b[j]==1){
		b[j]=0;
		--j;
	}
	b[j]=1;
	if(b[0]==1)
		return "";
	string tmp;
	tmp="";
	for(int i=1;i<=n;++i)
		if(b[i]==1)
			tmp+=s[i];
	return tmp;
}
#define fif(x,y) if((s[i]==x&&s[j]==y)||(s[i]==y&&s[j]==x))
bool check(string s){
	if(s.size()<3)
		return false;
	if(s[s.size()/2]!='w'||s[s.size()/2-1]!='i'||s[s.size()/2+1]!='i')
		return false;
	for(int i=0;i*2<s.size();++i){
		int j=s.size()-i-1;
		if(s[i]=='w'&&s[j]=='w')
			continue;
		if(s[i]=='i'&&s[j]=='i')
			continue;
		fif('(',')')
			continue;
		fif(')','(')
			continue;
		fif('[',']')
			continue;
		fif('{','}')
			continue;
		fif(']','[')
			continue;
		fif('}','{')
			continue;
		return false;
	}
	return true;
}
int main(){
	init();
	string t;
	int maxv=0;
	while((t=next())!=""){
		if(check(t))
			maxv=max(maxv,int(t.size()));
	}
	cout<<maxv<<endl;
}
```

---

