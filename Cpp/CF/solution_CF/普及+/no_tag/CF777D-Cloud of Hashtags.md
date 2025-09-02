# Cloud of Hashtags

## 题目描述

Vasya is an administrator of a public page of organization "Mouse and keyboard" and his everyday duty is to publish news from the world of competitive programming. For each news he also creates a list of hashtags to make searching for a particular topic more comfortable. For the purpose of this problem we define hashtag as a string consisting of lowercase English letters and exactly one symbol '\#' located at the beginning of the string. The length of the hashtag is defined as the number of symbols in it without the symbol '\#'.

The head administrator of the page told Vasya that hashtags should go in lexicographical order (take a look at the notes section for the definition).

Vasya is lazy so he doesn't want to actually change the order of hashtags in already published news. Instead, he decided to delete some suffixes (consecutive characters at the end of the string) of some of the hashtags. He is allowed to delete any number of characters, even the whole string except for the symbol '\#'. Vasya wants to pick such a way to delete suffixes that the total number of deleted symbols is minimum possible. If there are several optimal solutions, he is fine with any of them.

## 说明/提示

Word $ a_{1},a_{2},...,a_{m} $ of length $ m $ is lexicographically not greater than word $ b_{1},b_{2},...,b_{k} $ of length $ k $ , if one of two conditions hold:

- at first position $ i $ , such that $ a_{i}≠b_{i} $ , the character $ a_{i} $ goes earlier in the alphabet than character $ b_{i} $ , i.e. $ a $ has smaller character than $ b $ in the first position where they differ;
- if there is no such position $ i $ and $ m<=k $ , i.e. the first word is a prefix of the second or two words are equal.

The sequence of words is said to be sorted in lexicographical order if each word (except the last one) is lexicographically not greater than the next word.

For the words consisting of lowercase English letters the lexicographical order coincides with the alphabet word order in the dictionary.

According to the above definition, if a hashtag consisting of one character '\#' it is lexicographically not greater than any other valid hashtag. That's why in the third sample we can't keep first two hashtags unchanged and shorten the other two.

## 样例 #1

### 输入

```
3
#book
#bigtown
#big
```

### 输出

```
#b
#big
#big
```

## 样例 #2

### 输入

```
3
#book
#cool
#cold
```

### 输出

```
#book
#co
#cold
```

## 样例 #3

### 输入

```
4
#car
#cart
#art
#at
```

### 输出

```
#
#
#art
#at
```

## 样例 #4

### 输入

```
3
#apple
#apple
#fruit
```

### 输出

```
#apple
#apple
#fruit
```

# 题解

## 作者：奥特战士 (赞：5)

### 前情提要
>我会做的题都是傻X题，所以这道题就是傻X题  
——某dalao

------------
# 正文
## 分析题面

>给出$n$个开头是'#'的字符串,你需要把这些字符串按字典序从小到大排列.  
你可以把某一个字符串的任意后缀去掉(当然你甚至可以去掉整个字符串),要求你去掉的字符数量最少.  
输出你操作完的这$n$个字符串.

![稍加思索](https://ss3.bdstatic.com/70cFv8Sh_Q1YnxGkpoWK1HF6hhy/it/u=2995028456,1422359237&fm=26&gp=0.jpg)

不难发现，虽然题目里有 _排列、字典序_ 等字眼，但是这好像……**并不是一道排序题**……

相反，这是对每个字符串的**单个处理**

![](https://ss1.bdstatic.com/70cFvXSh_Q1YnxGkpoWK1HF6hhy/it/u=2781194016,2044444037&fm=26&gp=0.jpg)

简单来说，就是删掉每个字符串**最少**的**后缀**，让所有的字符串满足**字典序从小到大**，也就是第$i$个字符串的字典序**严格小于**第$i+1$个字符串

所以说，我们可以采用**从后往前**进行处理的思想

让第$i-1$个字符串删到**刚好**小于第$i$个字符串

第$n$个字符串不用做任何处理，因为**只要删除后缀就一定会减小字典序**

## 代码实现
### 法一
需要函数：$substr$（截取子串）

具体用法：
```cpp
字符串名称（string类型）.substr(起点位置,截取长度);
```
法一的思想与前文**分析题面**一致

对第$i-1$个字符串**从后往前**进行遍历

当$j$遍历到删去$j$以后的字符**恰好**可以让第$i-1$个字符串小于第$i$个

我们就**反其道而行之**，化删除为**截取**

也就是截取$j$之前（包括$j$)的字符串

核心代码如下：
```cpp
for(int i=n;i>1;i--){
	int len=s[i].size();
	for(int j=len-1;j>=0;j--){
		string tmp=s[i-1].substr(0,j+1);
		if(tmp<=s[i]){
			s[i-1]=tmp;
			break;
		}
	}
}
```
不难发现，对于$j$遍历到的每一个位置

**都需要调用一遍$substr$函数**

**并且对两个字符串进行比较**

效率很不优秀

![](https://ss0.bdstatic.com/70cFvHSh_Q1YnxGkpoWK1HF6hhy/it/u=1623132418,3665102574&fm=26&gp=0.jpg)

### 法二
看到前文我嫌弃效率不优秀的盆友

是不是觉得我要放弃$string$了？

然而……并不是

而是用另外一个函数：$erase$

![](https://ss0.bdstatic.com/70cFvHSh_Q1YnxGkpoWK1HF6hhy/it/u=3299279567,853265545&fm=26&gp=0.jpg)

~~因为STL实在是太好用了啊啊啊啊~~

具体用法：
```cpp
字符串名称（string类型）.erase(起点位置,删除长度);
```

不同于$substr$的是

只要一用$erase$，原来的字符串就会**自动删除**

所以如果想要保留原字符串的盆友还是建议**多用一个字符串来存储**

言归正传

法二的思想保留了题面的**删除**

但是并不是从**后缀**入手

我们先来看字典一般是怎么排序的：
>设想一本英语字典里的单词，何者在前何者在后？  
显然的做法是先按照第一个字母、以 a、b、c……z 的顺序排列；如果第一个字母一样，那么比较第二个、第三个乃至后面的字母。如果比到最后两个单词不一样长（比如，sigh 和 sight），那么把短者排在前。  
通过这种方法，我们可以给本来不相关的单词强行规定出一个顺序。“单词”可以看作是“字母”的字符串，而把这一点推而广之就可以认为是给对应位置元素所属集合分别相同的各个有序多元组规定顺序：下面用形式化的语言说明

引自[百度百科](https://baike.baidu.com/item/%E5%AD%97%E5%85%B8%E5%BA%8F/7786229?fr=aladdin)

聪明的小伙伴们已经发现了

我们可以**从前往后一位一位地比较**

如果第$i$个字符串在某一位上大于第$i-1$个字符串，就可以**不进行操作**

反之，**这一位就是我们要删除的起点**

核心代码如下：
```cpp
for(int i=n;i>1;i--){
	int len=s[i-1].size();
	int j;
	bool f=0;//s[i-1]是否小于等于s[i]
	for(j=0;j<len;j++){
		if(s[i][j]!=s[i-1][j]){
			if(s[i][j]>s[i-1][j])f=1;
			break;
		}
	}
	if(f)continue;
	if(j!=len)s[i-1].erase(j,len-j);
}
```
这样一来，**就只需要调用一次函数**

**并且不用再针对每个子串多次比较**

![](http://wx2.sinaimg.cn/large/ceeb653ely1g5298k6rifj205i03zq2v.jpg)
## 整体代码
AC代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n;
string s[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=n;i>1;i--){
		int len=s[i-1].size();
		int j;
		bool f=0;
		for(j=0;j<len;j++){
			if(s[i][j]!=s[i-1][j]){
				if(s[i][j]>s[i-1][j])f=1;
				break;
			}
		}
		if(f)continue;
		if(j!=len)s[i-1].erase(j,len-j);
	}
	for(int i=1;i<=n;i++)cout<<s[i]<<endl;
	return 0;
}
```


---

## 作者：Zzzzzzzm (赞：3)

首先本题为时间复杂度O($500000^2$)，空间复杂度O($500000^2$)所以不管怎么搞如果数据强一定是不行的，那么我们怎么过这道bt题呢？

~~巧妙利用数据太水~~——

#### 那就让我们快乐打暴力吧

因此我们会发现无论如何删除后缀都是无法增大该数列的字典序的，而必定会减小该数列，所以我们从最后查找，因为最后一个需要最大，而前面所有的都需要按照后面的数列调整。例如要想确定第一个就需要知道第二个，想要知道第二个就要知道第三个......因此我们从最后面往前模拟就能得到正解。

我们用lenth来存储当前最大长度，因为我们是从后往前查找，此时也就是最优长度，即答案。

我们每次比较第i个和第i-1个，当找到第一个不同时即可判断，若是i个比i-1大，那么就一定成立，lenth不变，弹出；反之则lenth=当前长度；若相等则找下一位。找完后进行判断，如果i的lenth更大则无需判断，若i-1的lenth更大则令lenth[i-1]=lenth[i]。

```cpp
#include<bits/stdc++.h>
using namespace std;

string s[500005];								//若极限数据炸上天 
int n;
int lenth[500005];

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> s[i];
		lenth[i] = s[i].size();
	}
	for(int i = n; i > 1; i--){
		if(lenth[i] < lenth[i-1]){				//若前面的lenth更大 
			int flag = 0;
			for(int j = 1; j < lenth[i]; j++){	//枚举第i个数列 
				if(s[i][j] > s[i-1][j]){
					flag = 1;
					break;
				}
				if(s[i][j] < s[i-1][j]){
					flag = 1;
					lenth[i-1] = j;
					break;
				}
			}
			if(!flag)							//判断有没有确定大小过 
				lenth[i-1] = lenth[i];			//若没有确定过那么前面的lenth=后面lenth 
			continue;
		}
		if(lenth[i] >= lenth[i-1]){				//若后面的lenth更大，则无需判断若前面的长带来的影响 
			for(int j = 1; j < lenth[i-1]; j++){
				if(s[i][j] > s[i-1][j]){
					break;
				}
				if(s[i][j] < s[i-1][j]){
					lenth[i-1] = j;
					break;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){				//可能炸裂输出 
		for(int j = 0; j < lenth[i]; j++){
			cout << s[i][j];
		}
		printf("\n");
	}
}
```


---

## 作者：Skies (赞：1)

看到这题，算了一下输入量，发现ta已经达到N*T=1e8数量级了（读者可以自行算算），肯定过不了，但还是打了打，没想到过了

### 思路

为了让删除的数量最少，我们一定**不能删除最后一个数**

因为他是最大的，删除他只会减小所有数的上限。

其次，主要的代码就是

##### 比较相邻两个字符串，删除后缀直到满足条件

但是这样还过不了，要加一个小优化。

因为空格比任何字符都小，所以如果不满足条件，可以直接删除到相同长度即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void rd(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void wr(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) wr(x/10);
    putchar(x%10^48);
    return ;
}
const int N=5e6+10;
string s[N];
int n;
int main(){
	rd(n);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(int i=n;i>=2;i--)
	{
		if(s[i]<s[i-1])//小优化
		{
			s[i-1]=s[i-1].substr(0,min(s[i].size(),s[i-1].size()));
		}
		while(s[i-1]>s[i])//删除到满足条件为止
		{
			s[i-1].erase(s[i-1].end()-1);
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<s[i];//输出答案
		putchar('\n');
	}
    return 0;
}
```



---

## 作者：ttq012 (赞：0)

不是真的就是纯暴力是吧？？代码最好写的一集。

考虑倒着贪心。容易发现为了让删除的字符的数量最小，应当贪心的保留最后一个字符串。剩下的字符串贪心的删除最后一个字符直到满足字典序关系即可。上述的东西不用哈希加二分，可以直接暴力模拟。

鉴定为：1.51s / 2.00s。

```cpp
#include <bits/stdc++.h>
#define F(i,x,y) for (int i = x; i <= y; ++i)
#define G(i,x,y) for (int i = x; i >= y; --i)
#define int long long
using namespace std;
const int N = 500100;
string s[N];
signed main() {
    int n;
    cin >> n;
    F(i, 1, n) {
        cin >> s[i];
    }
    G(i, n - 1, 1) {
        while (s[i] > s[i + 1]) {
            s[i].pop_back();
        }
    }
    F(i, 1, n) {
        cout << s[i] << '\n';
    }
    return 0;
}
```

---

## 作者：Epoch_L (赞：0)

## Solution
注意本题的字符串**总共**的长度不超过 $5\times 10^5$，题面中的 `total` 表示很明确，而其它题解有说数据水，其实并没有，复杂度是足以通过的。

考虑到正着做好像很难做到，因为不知道要删多少合适，所以不妨考虑倒着做，完整地保留第 $n$ 个串，向前枚举，再贪心保留尽可能多的字符即可。

证明也很显然，如果当前串的某一位的字典序比它后一个的字典序大，你只能把当前位置及后面的全删掉。假如不这样做，后一个串就得这样操作，但是长度短的应该放前面，不符合条件。

## Code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=500007;
string c[N];
int pos[N];
int main(){
  int n;read(n);
  for(int i=1;i<=n;i++)cin>>c[i];
  pos[n]=c[n].size();
  for(int i=n-1;i>=1;i--)
    for(int j=0;j<=min((int)c[i+1].size()-1,pos[i+1]-1);j++){
      if(c[i][j]==c[i+1][j])pos[i]++;
      else if(c[i][j]<c[i+1][j]){pos[i]=c[i].size();break;}
      else break;
    }
  for(int i=1;i<=n;i++){
    for(int j=0;j<=pos[i]-1;j++)putchar(c[i][j]);
    putchar('\n');
  }
  return 0;
}
```

---

## 作者：Tenshi (赞：0)

## 分析

一眼看过去以为是 dp，想了一下发现只是一道思维题。

考虑从上到下决策如何删除似乎无从下手，因为你无法简单地判定当前串删多了还是删少了。

那么考虑从下到上删除（也就是倒着删除），考虑枚举当前串的位置和下一个串对应位置比较:

- 如果发现当前串前 $k$ 位和下一个串相等，那就继续扫描。

- 如果当前串第 $k$ 位小于下一个串，说明我们可以贪心地保留全部当前串。

- 如果发现当前串第 $k$ 位大于下一个串，那么当前串的第 $k$ 位及后面的部分都要删掉。


```cpp
#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)

const int N=5e5+5;

string s[N];
int n;
int r[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n;
	rep(i,1,n) cin>>s[i];
	
	r[n]=s[n].size();
	dwn(i,n-1,1){
		int &res=r[i];
		rep(j,0,min((int)s[i].size()-1, r[i+1]-1)){
			if(s[i][j]==s[i+1][j]) res++;
			else if(s[i][j]<s[i+1][j]){
				res=s[i].size();
				break;
			}
			else break;
		}
	}
	
	rep(i,1,n){
		rep(j,0,r[i]-1) cout<<s[i][j];
		cout<<endl;
	}
	
	return 0;
}
```

---

## 作者：Mr_WA的大号 (赞：0)

代码不规范，WA两行泪。小学生又来发题解了！

题号：CF777D

难度：★★★

算法：字符串

## 开课了！

这题考验的就是大家的字符串基本功，只要字符串过关了，再加上一些数学思维就可以了。废话不多说，现在开始讲题目。

这一题题目意思并不难懂，就是给字符串上去一些后缀（或者不删），让它们成为一个有序的序列（但是#不能删）。

题目要去掉的最少，换一句话说就是留下的尽量多。这样的话我们的最后一个就应该不删才能保留最多。接下来我们就应该逐位满足了。

我们从n-1位开始，每位都与下一个字符串的当前这位对比，及：st[i][j]与st[i+1][j]这两位对比。如果st[i][j]比st[i+1][j]小的话，就代表不用删；大的话，就从这一位开始之后的每一位都要删；等于的话，就继续判断。当st[i]等于st[i+1]，也是不用删的。

按照以上方法一直到第1个字符串，就能完成了。

在这里给大家推荐一条语句：st.substr(开始点，结束点+1），他会在代码中起到妙用，能很快地截断字符串。

课讲完了，上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<iomanip>
using namespace std;
int n,x;
string st[500010];
int check(string st1,string st2)
{
	int len=0;//当前这一位设为0
	while(len<st1.size()||len<st2.size())//这位判断，如果有一位没有到最后就继续
	{
		if(st1[len]<st2[len])return 0;//当前这一位更小就不用删
		if(st1[len]>st2[len])return len;//大的话从当前这一位开始删去
		len++;
	}
	return 0;//一样的话也不用删
}
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>st[i];//输入
	for(int i=n-1; i>=1; i--)//从n-1位到1位判断
	{
		x=check(st[i],st[i+1]);//判断是否要删
		if(x>0)st[i]=st[i].substr(0,x);//截断字符串
	}
	for(int i=1; i<=n; i++)
		cout<<st[i]<<endl;//输出
	return 0;
}

```
祝大家能AC！

---

## 作者：Blue_wonders (赞：0)

## 判定字符串是否符合要求
#### 从最后开始正向判定字符串


------------

#### 思路
1. 首先从最后开始判定，因为最后一个一定不用删，而且比前面所有的都要大才能符合规范
2. 如果上一个字符串在x位置大于了下一个字符串，那么从x开始往后的都要删掉才能符合规范
3. 最后输出
#### 举例：
```
3
#book
#bigtown
#big
```
首先判断2,3两个字符串，发现第一个不一样的是第4个字母，所以字符串2在't'的时候字典序一定超过了字符串3，所以将第4个字母及以后全都删掉
```
3
#book
#big
#big
```
然后依次判断1,2字符串，发现在第2个时候'o'>'i'所以第一个'o'及以后所有字符串删掉
```
3
#b
#bigtown
#big
```
#### 代码
[AC详情](https://www.luogu.org/recordnew/show/19469649)
```cpp
#include<cstdio>//这个不知道为啥用万能库会unknown error 
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
struct str{
    string s;
}h[500010];//结构体定义许多个字符串(也许可以直接定义字符串数组更省事)
int n;
int cmp(string a,string b){//比较字符串大小 
    int x=0;
    while(a[x]!=0||b[x]!=0){//针对两个一样的字符串，在最后就会结束，不然会死循环 
        if(a[x]>b[x])return 0;//如果发现前面的字母已经小于了，就不用更改了 
        if(a[x]<b[x])return x;//如果不符合规范，就返回错误的值 
        x++;
    }
    return 0;//如果没有不一样的，就不更改了 
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)cin>>h[i].s;//输入字符串 
    for(int i=n-1;i>=1;i--){//从最后一个开始判断 
    	int p=cmp(h[i+1].s,h[i].s);//如果格式不符合规范，就输出最早不符合规范的数字 
    	if(p>0)h[i].s=h[i].s.substr(0,p);//删除掉不符合的 
	}
    for(int i=1;i<=n;i++)cout<<h[i].s<<endl;//输出 
    return 0;
} 
```


---

