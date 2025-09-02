# [BalticOI 2014] Three Friends (Day1)

## 题目描述

有一个字符串 $S$，对他进行操作：

1. 将 $S$ 复制为两份，存在字符串 $T$ 中
2. 在 $T$ 的某一位置上插入一个字符，得到字符串 $U$

现在给定 $U$，求 $S$。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（35 pts）：$N \le 2001$。
- Subtask 2（65 pts）：无特殊限制。

对于 $100\%$ 的数据，$2 \le N \le 2 \times 10^6+1$，保证 $U$ 中只包含大写字母。

#### 说明

翻译自 [BalticOI 2014 Day1 B Three Friends](https://boi.cses.fi/files/boi2014_day1.pdf)。

## 样例 #1

### 输入

```
7
ABXCABC```

### 输出

```
ABC```

## 样例 #2

### 输入

```
6
ABCDEF```

### 输出

```
NOT POSSIBLE```

## 样例 #3

### 输入

```
9
ABABABABA```

### 输出

```
NOT UNIQUE```

# 题解

## 作者：LongDouble (赞：42)

看了下题解，全是哈希。

这里写一个更简单的做法。

### 思路

由题意可知 $N$ 得为奇数，$S$ 才存在，所以先特判 $N$ 为偶数的情况。

由题意可知 $S$ 的长度为 $\lfloor \dfrac {N}{2}\rfloor$， 设 $S$ 的长度为 $M$。

因为只插入一个字符，所以如果存在 $S$，则 $U$ 的前 $M$ 个字符或后 $M$ 个字符中一定有一边是 $S$。

所以可以用 substr 函数分别截取前 $M$ 个字符和后 $M$ 个字符，再依次匹配检查是否合法。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a1, a2;
string u, s1, s2;

int main()
{
	scanf("%d", &n);
	if (n % 2 == 0)
	{
		printf("NOT POSSIBLE\n");
		return 0;
	}
	cin >> u;
	m = n / 2;
    
	s1 = u.substr(0, m); //匹配检查前M个字符
	int j = 0;
	for (int i = m; i < n && j < m; i++) 
		if (u[i] == s1[j]) j++;
	if (j == m) a1 = 1;
    
	s2 = u.substr(n - m, m); //匹配检查后M个字符
	j = 0;
	for (int i = 0; i < n - m && j < m; i++)
		if (u[i] == s2[j]) j++;
	if (j == m) a2 = 1;
    
	if (!a1 && !a2) printf("NOT POSSIBLE\n");
	else if (a1 && a2 && s1 != s2) printf("NOT UNIQUE\n");
	else if (a1) cout << s1 << endl;
		else cout << s2 << endl;
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：25)

这一题用哈希就可以水掉了。需掌握求一个字符串区间哈希值的做法。

## 题目大意
**尊重原题**：有 $3$ 个好朋友喜欢一起玩游戏，$A$ 君写下了一个字符串 $S$，$B$ 君将其复制一遍得到 $T$，$C$ 君在其任意位置（**包括首尾**）插入一个字符得到一个字符串 $U$。现在你得到了 $U$，请找出 $S$。

**简化版**：有一个字符串 $S$，对其进行操作：

- 将 $S$ 复制为两份，存在字符串 $T$ 中；
- 在 $T$ 的某一位置上插入一个字符，得到字符串 $U$。

现在给定 $U$，求 $S$。

## 大体思路
#### 前置芝士：字符串哈希
如果对字符串哈希不甚了解，请自行参考 [这题](https://www.luogu.com.cn/problem/P3370)。

此处介绍的，即是最常见的一种哈希：进制哈希。进制哈希的核心便是给出一个固定进制 $base$，将一个串的每一个元素看做一个进制位上的数字，所以这个串就可以看做一个 $base$ 进制的数，那么这个数就是这个串的哈希值；则我们通过比对每个串的的哈希值，即可判断两个串是否相同。

首先选择两个质数。我选择 $22783$ 作为底数（这是我们班一个人的学号），并用 `unsigned long long` 自然溢出的特性作为模数。下方所有变量未经特殊说明均为无符号长整形。（详见代码）

接下来进行预处理：用一个数组 $pre_k$ 表示 $base^k$，并滚动处理字符串哈希值 $H_i=H_{i-1}\times base + S_i$，其中 $H_i$ 表示哈希值，$S_i$ 为字符串中的元素。

```cpp
    pre[0]=1;//边界条件：base 的 0 次方等于一。
    for(int i= 1;i<=n;i++) {
        pre[i]=pre[i-1]*22783;//记录 pre 数组
        h[i]=h[i-1]*22783+(s[i]-'A'+1);//滚动处理哈希值
    }
```
在得到字符串哈希值后，如何求区间的哈希值呢？其实类似前缀和的思想，$hash[l,\ r]=H_r-H_{l-1}\times pre_{r-l+1}$。显然单纯的相减是不可取的，因此需要将区间前一项乘以底数的区间长度次幂，以求得字符串的区间哈希值。

而题目是插入了一个字符，因此我们逆向处理时需枚举删去一个字符的哈希值。类似上方，删去第 $x$ 个字符后的哈希值为 $hash[1,x-1]\times pre_{r-x} + hash[x+1,r]$。对于整个字符串而言，$l=1,r=n$。

```cpp
inline unsigned long long check(int l, int r) { 
	return h[r] - h[l - 1] * pre[r - l + 1]; 
}//区间哈希值
inline unsigned long long sum(int l, int r, int k) { 
	return check(l, k - 1) * pre[r - k] + check(k + 1, r); 
}//删去第 k 个字符
```

#### 本题详解
首先一个很显然的结论：由于 $U$ 串是 $S$ 串复制两次后插入一个字符所得，因此长度必然为奇数。所以特判：若 $n$ 为偶数则直接输出 `NOT POSSIBLE`。

接下来，将得到的字符串分成两部分 $1\sim mid,\ mid+1\sim n$，并分别记录这两段的哈希值。然后对于 $mid+1\sim n$，枚举删去 $1\sim mid$ 中的字符，若所得字符串与后半段相等则答案数 $ans+1$ 并跳出循环。反之亦然。

然后进行判断：
- 若答案数为零，则无解，输出 `NOT POSSIBLE`。

- 若答案数为一，或删去字符后的两串相等，则输出删去后不为空的字符串（即所求的 $S$）。

- 否则说明答案不唯一，输出 `NOT UNIQUE`。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 2000002
string a, b, c, d;
int n, mid, l1, l2, h[maxn], pre[maxn], ans;
char s[maxn];
inline unsigned long long check(int l, int r) { 
	return h[r] - h[l - 1] * pre[r - l + 1]; 
}//区间哈希值
inline unsigned long long sum(int l, int r, int k) { 
	return check(l, k - 1) * pre[r - k] + check(k + 1, r); 
}//删去字符
int main() {
    scanf("%d%s",&n,s+1);
    mid=(n+1)>>1;
    if (!(n&1)){
    	printf("NOT POSSIBLE");
		return  0;
	}//特判
    pre[0]=1;
    for(int i= 1;i<=n;i++) {
        pre[i]=pre[i-1]*22783;
        h[i]=h[i-1]*22783+(s[i]-'A'+1);
    }//预处理
    l1=check(mid+1,n);
    for(int i=mid+1;i<=n;i++) a.push_back(s[i]);
    for(int i=1;i<=mid;i++) {
        l2=sum(1,mid,i);
        if (l1==l2){
            ans++;
            c=a;
            break;
        }
    }
    l2=check(1,mid-1);
    for(int i=1;i<mid;i++) b.push_back(s[i]);
    for(int i=mid;i<=n;i++) {
        l1=sum(mid,n,i);
        if(l1==l2) {
            ans++;
            d=b;
            break;
        }
    }//枚举
    if (!ans)
        printf("NOT POSSIBLE");
    else if (ans == 1 || c == d)
        cout << (c.size() ? c : d);
    else printf("NOT UNIQUE");//判断输出
    return 0;
}
```
## 后记
今天 CSP2020 出成绩，普及组正常 1=，提高组因为 T3 加了 `ios::sync_with_stdio(0);` 语句而抱灵，导致 1= 没了，悲痛。

希望 NOIp rp++！

---

## 作者：newbie666 (赞：9)

此题用hash好一点，仁者见仁智者见智哈，本人只是觉得

Hash
方便，好想。

不废话了，直接上代码吧，注释在代码里：
### code:
```cpp
#include<bits/stdc++.h>
#define SIZE 2000005
const int base=999983;
using namespace std;
int n,mid;
string s;
unsigned long long power[SIZE],hs[SIZE],rt,lt;
map<unsigned long long, int> vis;
int get_hash(int l,int r){//获取区间hash
	return hs[r]-hs[l-1]*power[r-l+1];
}
int re_hash(int l,int r,int pos){ //在[l, r]中删去pos重新hash
	return get_hash(l,pos-1)*power[r-pos]+get_hash(pos+1,r);
}
bool check(int pos){ //pos断点
	if(pos==mid){
		lt=get_hash(1,pos-1);
		rt=get_hash(pos+1,n);
		return lt==rt;
	}
	else if(pos<mid){
		lt=re_hash(1,mid,pos);
		rt=get_hash(mid+1,n);
		return lt==rt;
	}
	else{
		lt=get_hash(1,mid-1);
		rt=re_hash(mid,n,pos);
		return lt==rt;
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); //输入输出加速 
	cin>>n;
	cin>>s;
	s="0"+s;
	mid=(n+1)>>1; //取字符串的中点下标
	power[0]=1;
	string s1=s.substr(mid+1,n);
	string s2=s.substr(1,mid-1);
	for(int i=1;i<=n;i++){
		power[i]=power[i-1]*base;
		hs[i]=hs[i-1]*base+s[i];
	}
	int mark,ans=0; //mark记录pos的位置， ans统计满足条件的pos的数量
	for(int i=1;i<=n;i++){ //枚举Pos
		if(check(i)==1){ //删掉下标i的元素之后，能够得到俩个一样的子串
			unsigned long long tmp;
            mark=i;
			if(mark<=mid){ //输出
				tmp=rt;
			}
	    	else{
	    		tmp=lt;	
			}
			if(vis[tmp]>0) continue;
			vis[tmp] = 1;
			ans++; //记录答案总数
        }
	}
	if(ans>1){ //不唯一
		cout<<"NOT UNIQUE"<<endl;
	}
	else if(ans==0){ //没答案
		cout<<"NOT POSSIBLE"<<endl;
	}
	else{
		if(mark<=mid){ //输出
			cout<<s.substr(mid+1)<<endl;
		}
		else{
			cout<<s.substr(1,mid-1)<<endl;
		}
	}
	return 0;
}
```
完结撒花，谢谢大家！

---

## 作者：WarningQAQ (赞：5)

由于本蒟蒻太菜，想不到别的做法，所以看到题的第一反应是hash；
虽然hash确实在码量上比较多，但是它~~好写~~思维难度比较低；
# 分析
假设一个字符串的前缀哈希值记为 $h[i]$，进制为 $base$，那么显然 $h[i] = h[i-1] \times base + s[i]$.

记 $p[i]$ 为 $base$ 的 $i$ 次方，那么我们可以 $O(1)$ 得到一个字串的哈希值。
```cpp
inline unsigned long long check(int l,int r){
    return h[r]-h[l-1]*pre[r-l+1];
}
```


------------
其中，乘以 $p[r-l+1]$ 相当于左移了 $r-l+1$ 位。

同样，我们可以 $O(1)$ 得到字串中删除一个字符后的hash值。
```cpp
inline unsigned long long sum(int l,int r,int k){
    return check(l,k-1)*pre[r-k]+check(k+1,r);
}
```


------------
枚举每一个位置，剩下的应是两个相同的字符串，根据hash值判断一下。
## 上完整代码
```cpp
#include<cstdio>
#include<iostream>
#include"cstring"
using namespace std;
#define maxn 2000002
string a,b,c,d;
int n,mid,l1,l2,h[maxn],pre[maxn];
char s[maxn];
int ans;
inline unsigned long long check(int l,int r){
    return h[r]-h[l-1]*pre[r-l+1];
}
inline unsigned long long sum(int l,int r,int k){
    return check(l,k-1)*pre[r-k]+check(k+1,r);
}
inline void out(){
    if(!ans)printf("NOT POSSIBLE");
    else if(ans==1||c==d)cout<<(c.size()?c:d);
    else printf("NOT UNIQUE");
}
inline void work(){
    l1=check(mid+1,n);
    for(int i=mid+1;i<=n;i++)a.push_back(s[i]);
    for(int i=1;i<=mid;i++){
        l2=sum(1,mid,i);
        if(l1==l2){
            ans++;
            c=a;
            break;
        }
    }
    l2=check(1,mid-1);
    for(int i=1;i<mid;i++)b.push_back(s[i]);
    for(int i=mid;i<=n;i++){
        l1=sum(mid,n,i);
        if(l1==l2){
            ans++;
            d=b;
            break;
        }
    }
    out();
}
int main(){
    scanf("%d%s",&n,s+1);
    mid=(n+1)>>1;
    if(!(n&1))return printf("NOT POSSIBLE"),0;
    pre[0]=1;
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]*733;
        h[i]=h[i-1]*733+(s[i]-'A'+1);
    }
    work();
    return 0；
}
```


------------
求过QAQ

打广告[blog](https://www.cnblogs.com/nakiri-ayame-suki/)

---

## 作者：WangYunpei (赞：4)

 看到这道题，我本能的想到了字符串hash不知道字符串hash的请看下面
 字符串hash
 要知道字符串hash得先知道整数hash，整数hash的原理是给每个整数分配一个hash值，hash值是由这个整数模一个固定整数得到的，假如有两个数不一样但hash值一样，这时就要用到vector，vector相当于一个不用固定大小的数组，整数hash的时间复杂度平均为$O(n)$,最坏为$O(n^2)$，整数hash代码如下(这是P4305)
```cpp
#include <bits/stdc++.h>//头文件
using namespace std;
const int mod=50021;//取hash值的模数
vector<unsigned long long> vec[10+mod];
int t,n,x;
unsigned long long hs(unsigned long long x){//取hash值的函数
	return 1ull*(x%mod);//1ull:定义一个unsigned long long的1，unsigned long long可以循环计数，很方便
}
bool add(int x){//加入进链表
	unsigned long long v=hs(x);//取hash值
	for(int j=0;j<vec[v].size();j++) //循环链表的每一个元素
		if(vec[v][j]==x)//如果已经有了这个元素
			return false;//退出
	vec[v].push_back(x);//将x插入链表
	return true;
}
int main(){
	cin>>t;//t组数据
	while(t--){
		memset(vec,0,sizeof(vec));//每组数据都要清空
		cin>>n;//n个数
		while(n--){
			cin>>x;
			if(add(x))//加入x
				cout<<x<<" ";	
		}
		cout<<endl;
	}
	return 0;
}
```
 接下来就是字符串hash了，大体思路是用进制将字符串转换成数字，版本1（【模板】字符串哈希）：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
unsigned long long base=131;//131进制可以直接取ascll码
unsigned long long a[10010];//hash值数组
int n,ans=1;
unsigned long long mod=1000037;//模数
unsigned long long hash(string s){//求hash值
	unsigned long long sum=0;
	for(int i=0;i<s.size();i++)
		sum=(sum*base+(unsigned long long)s[i])%mod;//进制转换
	return sum;
}
int main(){
	cin>>n;	
	for(int i=1;i<=n;i++){
 		cin>>s;
 		a[i]=hash(s);
	}
	sort(a+1,a+n+1);//排序
	for(int i=1;i<n;i++)
 		if(a[i]!=a[i+1])//比较
 			ans++;//答案数+1
	cout<<ans;
} 
```
 然后我们可以用一个公式将一个字符串的子串在$O(1)$的时间里求出来，先用一个类似前缀和的东西求出前i个字符的hash值，然后再用这个公式求出l~r的hash值：$hash[r]-hash[l-1]*base$^$(r-l+1)$但是，每次都求一个$base$^$(r-l+1)$会超时，所以就可以先初始化，但是，仔细研究这道题后就会发现，这道题还有一个坑点，来看个样例：ABAAB，按照原来那样，会有两个答案AB和AB，然后就错了，于是就可以用一个vis数组标记结果的hash值，然后就有了这道题的解法：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
const int maxn=2000005;
int n,mid;
unsigned long long hs[maxn],power[maxn];
string s;
int vis[130];
unsigned long long get_hash(int l,int r){//求l~r的hash值
    return hs[r]-hs[l-1]*power[r-l+1];
}
unsigned long long re_hash(int l,int r,int pos){//求l~r中删除pos的hash值
    return get_hash(l,pos-1)*power[r-pos]+get_hash(pos+1,r);
}
bool check(int pos){//判断删除pos是否可以
    unsigned long long left=0,right=0;
    if(pos==mid){//如果pos在正中间
        left=get_hash(1,pos-1);//求左边的hash值
        right=get_hash(pos+1,n);//求右边的hash值
        return left==right;//左右是否相等
    }
    else if(pos<mid){//如果pos在左区间
        left=re_hash(1,mid,pos);//求左边删除pos的hash值
        right = get_hash(mid+1, n);//求右边的hash值
        return left == right;//左右是否相等
    } 
    else{//如果pos在右区间
        left = get_hash(1, mid-1);//求左边的hash值
        right = re_hash(mid, n, pos);//求右边删除pos的hash值
        return left == right;//左右是否相等
    }
}
int main(){
    cin >> n;
    cin >> s;//字符串
    s="0"+s;//补1位
    mid=(n+1)>>1;//取中间，相当于(n+1)/2
    power[0]=1;//任何非0数的0次方等于1
    for(int i=1;i<=n;i++){//初始化
        power[i]=power[i-1]*13331;//n^i次方
        hs[i]=hs[i-1]*13331+s[i];//前i位的hash值
    }
    int mark,ans=0;
    for(int i=1;i<=n;i++)
        if(check(i)==true){//判断删除i可不可以
            mark=i;//可以的值
            ans++;//可以的数量
        }
    if(ans>1)//不止一个可以
        cout<<"NOT UNIQUE";
    else if(ans==0)//没有一个可以
        cout<<"NOT POSSIBLE";
    else{//只有一个可以
        if(mark<=mid)//可以的值在前半段
            cout<<s.substr(mid+1);//那么后半段就是答案
        else//可以的值在后半段
            cout<<s.substr(1,mid-1);//那么前半段就是答案
    }
    return 0;
}
```


---

## 作者：Suzt_ilymtics (赞：4)

### 写在前面

[P6739 [BalticOI 2014 Day1] Three Friends](https://www.luogu.com.cn/problem/P6739)


听说这题可以用比较暴力的做法过，比如 $string$ 里面自带的 $substr$ ，可以看这位大佬的[提交记录](https://www.luogu.com.cn/record/44542371)

~~模数不要用 $49999$ ，会被卡， $1e9+9$ 才是真爱~~

### Solution

#### 字符串哈希（可跳过）：

由于字符串是具有前后关系的，可以按下述方法构造：
选取两个合适的互质常数 $b$ 和 $h (b < h)$， 假设有一个字符串 $C = c_1c_2···c_m$，那么我们定义哈希函数：

$$H(C) = (c_1b^{m - 1} + c_2b^{m - 2} + ···+c_mb^{0}) \mod h$$

考虑递推实现，设 $H(C, k)$ 为前 $k$ 个字符构成的字符串的哈希值，则：

$$H(C, k + 1) = H(C, k) \times b + c_{k + 1}$$

通常，题目要求的是判断主串的一段字符与另一个匹配串是否匹配，即判断字符串 $C = c_1c_2···c_m$ 从位置 $k + 1$ 开始的长度为 $n$ 的子串 $C^{'} = c_{k + 1}c_{k + 2}···c_{k + n}$ 的哈希值与另一匹配串 $S = s_1s_2···s_n$ 的哈希值是否相等，则：

$$H(C_{'}) = H(C, k + n) - H(C, k) \times b^{n}$$

只要预求得 $b^{n}$ ，就能 $O(1)$ 判断了

可以预处理出所有 $b^{n}$ 存在 $Pow$ 数组里

---------------------------------------

观察目标串 $U$ 的构造方式，发现如果 $N$ 是偶数，一定无法构造

然后考虑枚举删除每一个字符，再将剩下的字符串均分判断哈希值是否相等

假设删去的字符在前半段，那么后半段的一定是原字符串 $S$，如果在后半段，那么前半段一定是原字符串 $S$ ，

所以可以分开枚举，并且预处理出对应的原字符串

那么删掉一个字符后，剩下的两段怎么合并呢？以样例字符串为例：

 $$ABXCABC$$

假设枚举到 $X$

那么原字符串为 $ABC$，前面要合并的两段字符串是 $AB$，$C$

如果朴素计算这两个串的哈希值及原字符串哈希值，计算过程如下：

$$AB = A * b^{1} + B * b^{0}$$

$$C = C * b^{0}$$

$$ABC = A * b^{2} + B * b^{1} + C * b^{0}$$

所以不难看出 $ABC = AB * b^{1} + C$

对这个结论进行推广，对于字符串 $X$，删掉其中一个字符后，分成两个字符串$X_1,X_2$，有 

$$X = X_1 * b^{len_{X_2}} + X_2$$

根据这个公式去进行合并，然后比较两个字符串哈希值是否相同

然后这就可以了吗？   不不不

看这个样例

```cpp
13
AABCABCABCABC
```

我们会发现删掉第一个和第二个字符都可以，但得到的原串都是 $ABCABC$

所以注意开个map判重即可

~~如果还A不了，兄弟，改个模数试试吧~~

### Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 2e6+10;
const int INF = 1;
const int mod = 1e9+9;
const int b = 7;

int len, cnt = 0;
char s[MAXN];
LL Pow[MAXN], Pow2, sum, H[MAXN], wz;
map<LL, LL> Map;

int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return f ? -s : s;
}

int main()
{
	len = read();
	if(len % 2 == 0) {
		printf("NOT POSSIBLE");
		return 0; 
	} 
	cin>>(s + 1);
//	for(int i = 1; i <= len; ++i) {
//		cout<<s[i]<<" ";
//	}
//	cout<<"\n";
	Pow[0] = 1;
	for(int i = 1; i <= len; ++i){
		Pow[i] = Pow[i - 1] * b % mod;
		H[i] = (H[i - 1] * b % mod + s[i]) % mod;
	}
	sum = (H[len] - H[len / 2 + 1] * Pow[len / 2] % mod + mod) % mod; //后半段的哈希值 
	for(int i = 1; i <= len / 2 + 1; ++i){
		LL pre = H[i - 1] * Pow[len / 2 + 1 - i] % mod;//删掉枚举字符后的剩余字符串的哈希值 
		if(Map[sum] == 0 && sum == (H[len / 2 + 1] - H[i] * Pow[len / 2 + 1 - i] % mod + pre + mod) % mod){//算出后面那一段并进行拼接 
			cnt++;
			Map[sum]++;
			wz = i;
		}
	}
//	cout<<cnt<<"lkp\n";
	sum = H[len / 2];//前半段的哈希值 
	for(int i = len / 2 + 2; i <= len; ++i){
		LL pre = (H[i - 1] - H[len / 2] * Pow[i - len / 2 - 1] % mod + mod) % mod * Pow[len - i] % mod;//删掉枚举字符后的剩余字符串的哈希值 
		if(Map[sum] == 0 && sum == (H[len] - H[i] * Pow[len - i] % mod + pre + mod) % mod){//算出后面那一段并进行拼接 
			cnt++;
			Map[sum]++;
			wz = i;
		}
	} 
//	cout<<cnt<<"zsf\n";
	if(cnt == 0) printf("NOT POSSIBLE");
	else if(cnt == 1) {
		if(wz <= len / 2) for(int i = len / 2 + 2; i <= len; ++i) cout<<s[i];
		else for(int i = 1; i <= len / 2; ++i) cout<<s[i];
	}
	else printf("NOT UNIQUE"); 
	return 0;
}

```


---

## 作者：JK_LOVER (赞：3)

## 题意
将一个字符串复制一次，再插入一个字符。得到 $U$ ，求出原字符串。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p6739)
## 分析
既然是复制一次再插入，那么首先就应该想到，找出这个字符并将其删去，再判断剩下的是否相同。那么最朴素的做法时间复杂度为   $O(n^2)$ 。是通过不了的。那么现在算法的瓶颈在于如何快速比较两个字符串是否一致。学过的朋友应该想到，这个进制哈希可以做到 $O(1)$ 判断。那么现在这道题就做完了，时间复杂度为 $O(n)$ 。

- 小细节：一开始我交了很多次，发现有这样一组数据 $AAAAA...AAA$ ，这是只有一种唯一的方案的。

- 后面的点卡模数，稍微开大一点就过了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 2e6+100,Mod = 1e9+7,Base = 1314520; 
int hash[N],n,Pow[N],Ans = 0,pos,vis[30];
char ch[N];
int Sum(int l,int r){
	if(l > r) return 0;
//	cout<<((hash[r] - (hash[l-1] * Pow[r-l+1])%Mod)%Mod+Mod)%Mod<<endl;
	return ((hash[r] - (hash[l-1] * Pow[r-l+1])%Mod)%Mod+Mod)%Mod;
}
bool Same(int Mid){
	if(Mid < (n+1)/2){
		int L = (Sum(1,Mid-1) * Pow[(n+1)/2-Mid] % Mod + Sum(Mid+1,(n+1)/2)%Mod) % Mod;
		int R = Sum((n+1)/2+1,n);
//		cout<<L<<" "<<R<<endl;
		return L == R;
	}
	if(Mid == (n+1)/2){
		return Sum(1,Mid-1) == Sum(Mid+1,n);
	}
	if(Mid > (n+1)/2){
		int L = Sum(1,(n+1)/2-1)%Mod;
		int R = (1LL*Sum((n+1)/2,Mid-1) * Pow[n - Mid] % Mod + Sum(Mid+1,n)+Mod)% Mod;
		return L == R;
	}
}
signed main()
{
	int jud = 0;
	cin>>n;
	cin>>ch+1;
	if(!(n&1)) {printf("NOT POSSIBLE\n");return 0;}
	Pow[0] = 1;hash[0] = 0;
	for(int i = 1;i <= n;i++){
		hash[i] = (1LL*hash[i-1]*Base%Mod+(1LL*ch[i]-'A'+1))%Mod;
		Pow[i] = (1LL*Pow[i-1]*Base)%Mod;
//		cout<<hash[i]<<endl;
	}
	for(int i = 1;i <= n;i++){
		if(Same(i)){
			Ans++;
			pos = i;
			if(vis[ch[i]-'A'] && vis[ch[i]-'A']!=i-1) jud = 1;
			vis[ch[i]-'A'] = i;
		}
	}
	if(!Ans) cout<<"NOT POSSIBLE"<<endl;
	else if(Ans>1 && jud) cout<<"NOT UNIQUE"<<endl;
	else {
		if(pos < (n+1)/2){
			for(int i = (n+1)/2+1;i <= n;i++) printf("%c",ch[i]);
		}
		if(pos == (n+1)/2){
			for(int i = 1;i < pos;i++) printf("%c",ch[i]);
		}
		if(pos > (n+1)/2){
			for(int i = 1;i < (n+1)/2;i++) printf("%c",ch[i]);
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：happybob (赞：3)

这道题目有意思！dalao都用着hash，表示不懂，只好跟着第一篇题解的思路喽！代码量比hash少得多得多啊！

其实只要将n先除以2，前半段匹配后半段，后半段匹配前半段，注意n % 2 == 0要特判，不然会WA 3个点，0分！

```cpp
#include <iostream>
#include <cstring>
using namespace std;

string s, a, b;

int main()
{
    int n;
    cin >> n >> s;
    if(n % 2 == 0)//两个字符串加在一起加一个字符的长度只有可能是奇数
    {
        cout << "NOT POSSIBLE\n";
        return 0;
    }
    int x = n / 2;
    a = s.substr(0, x);//前半段
    b = s.substr(n - x, x);//后半段
    int l = 0;
    bool f1, f2;
    f1 = f2 = false;
    for(int i = x; i <= n - 1 && l < x; i++)
    {
        if(s[i] == a[l])
        {
            l++;
        }
    }
    if(l == x)//如果到最后有连续的可以匹配那就是true了
    {
        f1 = true;
    }
    l = 0;
    for(int i = 0; i <= n - x - 1 && l < x; i++)
    {
        if(s[i] == b[l])
        {
            l++;
        }
    }
    if(l == x)
    {
        f2 = true;
    }
    if(!f1 && !f2)//都不能匹配，不可能
    {
        cout << "NOT POSSIBLE\n";
    }
    else
    {
        if(f1 && f2 && a != b)//多种方法，因为前面和后面都匹配，注意a和b不能相等
        {
            cout << "NOT UNIQUE\n";
        }
        else
        {
            if(f1)
            {
                cout << a << endl;
            }
            else
            {
                cout << b << endl;
            }
        }
    }
    return 0;
}
```


---

## 作者：codecode (赞：3)

#### 题解：

注意到 $U$ 只比 $S+S=T$ 多一位，我们可以枚举多的是哪一位，然后按序比较剩下的字符串的前半段和后半段是否相同，时间复杂度 $\Theta(n^2)$, 可以通过 $\texttt{subtask1}$。

但是，由于 Hash 的存在，我们判断两个字符串相同无需按序比较，可以 Hash $\Theta(1)$ 判断，这样此题便做到了 $\Theta(n)$，可以通过 $\texttt{subtask2}$。

> [什么是 Hash](https://www.luogu.com.cn/problem/P3370)


------------

据某位学长说，**所有的单 Hash 都可以卡掉**，所以建议大家使用双 Hash（~~但是我懒~~）

#### 代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e6+233;
const int base=233;
const int mod=998244353; //只用了单Hash
int n,cnt,flag,mark;
int h[maxn],pw[maxn],b[30];
char a[maxn]; 
int sum(int l,int r){ //计算区间[l,r]的Hash值
    if(l>r)return 0;
    return ((h[r]-(h[l-1]*pw[r-l+1])%mod)%mod+mod)%mod;
}
int query(int pos){ //Hash判断剩下的两段是否相同，pos即断点
    int pre=0,nxt=0;
    if(pos==(n+1)/2){
        pre=h[pos-1];
        nxt=sum(pos+1,n);
        return pre==nxt;
    }
    if(pos<(n+1)/2){
        pre=((h[pos-1]*pw[(n+1)/2-pos])%mod+sum(pos+1,(n+1)/2))%mod;
        nxt=sum((n+1)/2+1,n);
        return pre==nxt;
    } 
    if(pos>(n+1)/2){
        pre=h[(n+1)/2-1];
        nxt=((sum((n+1)/2,pos-1)*pw[n-pos])%mod+sum(pos+1,n))%mod;
        return pre==nxt;
    }
}
signed main(){
    memset(b,-1,sizeof(b));
    cin>>n;
    cin>>a+1;
    int len=strlen(a+1);
    for(int i=1;i<=len;++i) //Hash预处理
        h[i]=((h[i-1]*base)%mod+(int)a[i]-'A'+1)%mod;
    pw[0]=1;
    for(int i=1;i<=n;i++)
        pw[i]=(pw[i-1]*base)%mod;
    for(int i=1;i<=n;i++) 
        if(query(i)){
            mark=i,cnt++; //记录可能的端点数量及端点位置
            if(b[a[i]-'A'+1]!=-1&&b[a[i]-'A'+1]!=i-1)flag=1;
            b[a[i]-'A'+1]=i;
        }
    if(flag&&cnt>1){cout<<"NOT UNIQUE";return 0;}
    if(cnt<1){cout<<"NOT POSSIBLE";return 0;}
    if(mark==(n+1)/2){ //输出
        for(int j=1;j<=mark-1;j++)putchar(a[j]);
    }
    else if(mark<(n+1)/2){
        for(int j=1;j<=mark-1;j++)putchar(a[j]);
        for(int j=mark+1;j<=(n+1)/2;j++)putchar(a[j]);
    }
    else if(mark>(n+1)/2){
        for(int j=(n+1)/2;j<=mark-1;j++)putchar(a[j]);
        for(int j=mark+1;j<=n;j++)putchar(a[j]);
            return 0;
        }
    return 0;
}
```

---

