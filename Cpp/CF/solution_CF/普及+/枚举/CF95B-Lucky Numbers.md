# Lucky Numbers

## 题目描述

Petya 非常喜爱幸运数字。大家都知道如果一个十进制正整数的各个数位中不包含除4或7以外的数，那么它就是幸运的。例如，47,774,4是幸运的，而5,17,467则不是。

当一个十进制幸运数字中含有4和7的数量相同时，这个幸运数字就是超级幸运的。例如，47,7744,474477是超级幸运的，而4,744,467则不是。

一天Petya偶然发现了一个正整数n。请帮他找出不小于n的最小的超级幸运数字。

## 样例 #1

### 输入

```
4500
```

### 输出

```
4747
```

## 样例 #2

### 输入

```
47
```

### 输出

```
47
```

# 题解

## 作者：FQR_ (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF95B)

我们可以把整道题分成两种情况来做。
___

### Part 1 当数字的长度为奇数

假设数字长度为 $len$ 。

因为不存在长度为奇数的**超级幸运数字**，所以答案就为长度为 $len + 1$ 的最小的**超级幸运数字**，也就是输出 $\frac{( len + 1 )}{2}$ 个 $4$ 和 $\frac{( len + 1 )}{2}$ 个 $7$ 。

给出代码：
```cpp
//字符串s在前面已定义过（string s）
cin>>s;
if(s.size()%2==1)//如果长度为奇数
{
	for(int i=0;i<(s.size()+1)/2;i++) cout<<4;
	for(int i=0;i<(s.size()+1)/2;i++) cout<<7;
	return 0;
}
```
___
### Part 2 当数字的长度为偶数

我们知道，长度为 $n$ 的**超级幸运数字**的最大值为 $\frac{n}{2}$ 个 $7$ 和 $\frac{n}{2}$ 个 $4$组合在一起。

所以我们可以判断输入的数字是否大于这个最大值。

如果大于这个最大值，就可以直接输出  $( \frac{n}{2} + 1 ) $ 个 $4$ 和 $ ( \frac{n}{2} + 1 ) $ 个 $7$ 。

给出这一部分的代码：
```cpp
string maxs;//maxs为长度为s.size()的超级幸运数字的最大值
for(int i=0;i<s.size()/2;i++) maxs+='7';
for(int i=0;i<s.size()/2;i++) maxs+='4';
if(maxs<s)//由于maxs和s为string类型，可以直接用"<"。
{
	for(int i=0;i<s.size()/2+1;i++) cout<<4;
	for(int i=0;i<s.size()/2+1;i++) cout<<7;
	return 0;
}
```

___

接下来就是普通情况了。这里我写了一个DFS。

```cpp
string ans;
void dfs(int p,int cnt_4,int cnt_7)
{
	if(ans<s) return;
	if(p==s.size())
	{
		cout<<ans;
		exit(0);
	}
	if(cnt_4<s.size()/2)
	{
		ans[p]='4';
		dfs(p+1,cnt_4+1,cnt_7);
	}
	if(cnt_7<s.size()/2)
	{
		ans[p]='7';
		dfs(p+1,cnt_4,cnt_7+1);
	}
}
```

其中， $p$ 表示当前填写数字的位置， $cnt\_4$ 表示当前数字4的数量，$cnt\_7$ 表示当前数字7的数量。

当 $ans$ 比 $s$ 还小，不管接下来怎么填，$ans$ 都比 $s$ 小，所以直接`return;`。

然后，判断是否已经填完数字。如果填完数字，可以直接输出。因为DFS中我们先的填 $4$ ,再填的 $7$ 。

最后，如果能填4或7，就填数。

在主函数里这样调用：
```cpp
for(int i=0;i<s.size();i++) ans+='9';//先把ans设为999999…，避免填过的数与输入数字前半部分一样，却返回了。
dfs(0,0,0);
```
___
下面给出完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,ans;
void dfs(int p,int cnt_4,int cnt_7)
{
	if(ans<s) return;
	if(p==s.size())
	{
		cout<<ans;
		exit(0);
	}
	if(cnt_4<s.size()/2)
	{
		ans[p]='4';
		dfs(p+1,cnt_4+1,cnt_7);
	}
	if(cnt_7<s.size()/2)
	{
		ans[p]='7';
		dfs(p+1,cnt_4,cnt_7+1);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>s;
	if(s.size()%2==1)
	{
		for(int i=0;i<(s.size()+1)/2;i++) cout<<4;
		for(int i=0;i<(s.size()+1)/2;i++) cout<<7;
		return 0;
	}
	string maxs;
	for(int i=0;i<s.size()/2;i++) maxs+='7';
	for(int i=0;i<s.size()/2;i++) maxs+='4';
	if(maxs<s)
	{
		for(int i=0;i<s.size()/2+1;i++) cout<<4;
		for(int i=0;i<s.size()/2+1;i++) cout<<7;
		return 0;
	}
	for(int i=0;i<s.size();i++) ans+='9';
	dfs(0,0,0);
	return 0;
}
```

---

## 作者：L2_sheep (赞：6)

题意求大于等于n的最小幸运数，（幸运数是只由4和7构成，且4和7的数量相等的数）。

首先可以知道幸运数的位数一定是偶数位的，如果n是奇数位的，直接输出(n+1)/2个4和(n+1)/2个7。

接下来，从n的最高位开始遍历：1. 如果n的这位数字（记为a[i])小于等于4, 4的个数（记为c4）就加1。

（1）如果c4已经超过了n的总位数的一半（记为h），把幸运数的这位数(记为b[i])设成7，停止遍历。
    
（2） 否则当a[i]小于4，停止遍历。当a[i]等于4，记录位置(记为p4[c4])以及当前b[i]等于7有多少个（记为c[c4])，继续遍历。
    
    
    
2.如果a[i]小于等于7，7的个数（记为c7）就加1。

（1）如果c7已经超过了h，找离它最近且c[c4]小于h的4的位置，把4改成7，停止遍历。
    如果没有这样的4的位置，做个标记，位数和n相等的幸运数不存在。
    
（2）否则当a[i]小于7，停止遍历。当a[i]等于7，继续遍历。
    
    
3.如果a[i]大于7，找离它最近且c[c4]小于h的4的位置，把4改成7，停止遍历。
如果没有这样的4的位置，做个标记，位数和n相等的幸运数不存在。
    
最后，输出符合要求结果即可。
程序的复杂度是线性的，代码如下：
    
  ```
#include <stdio.h>
#include <string.h>
#define N 100005

char a[N], b[N];
int p4[N], c[N];

int main() 
{
	int i, j, c4 = 0, l, h, c7 = 0, f = 0;
	
	scanf("%s", a);
	l = strlen(a);
	if(l & 1){
		h = (l + 1) >> 1;
		for(i = 0; i < h; i++) putchar(52);
		for(i = 0; i < h; i++) putchar(55);
		return 0;
	}
	else{
		h = l >> 1;
		for(i = 0; i < l; i++){
			if(a[i] <= 52){
				c4++;
				if(c4 > h){
					b[i] = 55;
					c4--, c7++;
					break;
				}
				else{
					b[i] = 52;
					if(a[i] < 52) break;
					p4[c4] = i;
					c[c4] = c7;
				}
			}
			else if(a[i] <= 55){
				c7++;
				if(c7 > h){
					while(c4 > 0 && c[c4] >= h) c4--;
					if(c4 == 0){
						f = 1;
					 	break;	
					}
					b[i = p4[c4]] = 55;
					c7 = c[c4] + 1;
					c4--;
					break;
				}
				else{
					b[i] = 55;
					if(a[i] < 55) break;
				}
			}
			else{
				while(c4 > 0 && c[c4] >= h) c4--;
				if(c4 == 0){
					f = 1;
					break;	
				}
				b[i = p4[c4]] = 55;
				c7 = c[c4] + 1;
				c4--;
				break;
			}
		}
	}
	if(f){
		i = h + 1;
		while(i--) putchar(52);
		i = h + 1;
		while(i--) putchar(55);
	}
	else{
		if(i == l) i--;
		for(j = 0; j <= i; j++) putchar(b[j]);
		i = h - c4;
		while(i--) putchar(52);
		i = h - c7;
		while(i--) putchar(55);
	}
	
	return 0;
}
```
    

---

## 作者：PR_CYJ (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/CF95B)
# 题意简述
这道题我们会得到一个数字串，而我们要求的是大于它的最小的超级幸运数。超级幸运数即只含有 $ 4 $ 和 $ 7 $ 且 $ 4 $ 和 $ 7 $ 出现次数相同的数。
# 思路分析
我们先判断这个数字串的长度，记作 $ n $。如果 $ n $ 为奇数，因为没有奇数位的超级幸运数，所以我们直接输出 $ \frac{(n+1)}{2} $ 个四，再输出 $ \frac{(n+1)}{2} $ 个七，即共 $ n+1 $ 位的最小超级幸运数。如果 $ n $ 为偶数，就直接 dfs。

在 dfs 时，我们按照题中顺序进行遍历，因为我们是按照先 $ 4 $ 后 $ 7 $ 的顺序 dfs 的，所以可以直接输出答案。

如果 dfs 完并没有输出答案，就说明这个数字串大于最大的 $ n $ 位超级幸运数，所以我们直接输出最小的 $ n+2 $ 位超级幸运数。
# AC代码
- **切勿抄袭！！！**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s,t;
inline void dfs(int k,int s1,int s2)//k代表当前位置，s1代表4的个数，s2代表7的个数 
{
	if (t<s)//剪枝 
		return;
	if (s1==s2&&s1+s2==n&&t>=s)
	{
		cout<<t<<endl;
		exit(0);
	}
	if (s1<n/2)
	{
		t[k]='4';
		dfs(k+1,s1+1,s2);
		t[k]='9';//回溯 
	}
	if (s2<n/2)
	{
		t[k]='7';
		dfs(k+1,s1,s2+1);
		t[k]='9';//回溯 
	}
}
int main()
{
	cin>>s;
	n=s.size();
	if (n%2)
	{
		for(int i=1;i<=(n+1)/2;i++)
			cout<<4;
		for(int i=1;i<=(n+1)/2;i++)
			cout<<7;
	}
	else
	{
		for(int i=1;i<=n;i++)
			t+='9';//将t设为最大值，避免dfs剪枝时错误跳出 
		dfs(0,0,0);
		for(int i=1;i<=n/2+1;i++)
			cout<<4;
		for(int i=1;i<=n/2+1;i++)
			cout<<7;
	}
}
```

---

## 作者：Hu_Tao (赞：3)

# ~~某蒟蒻的第一篇题解。。。~~

先说一下题目意思.

一个人~~吃饱了撑着~~定义了一种数(下面简称"幸运数"),这种数的数位只包含4和7(0也不行),且4和7数量相等.
比如:4477,47,4774都是幸运数,而1,4777,474745都不是.
下面让你求≥n的最小幸运数.

下面是题解部分:

我们假设n的位数为n0.

很显然,先特判两种情况:

情况一,n0为奇数,很显然在n0位的数中,肯定不会有别的幸运数了,此时输出(n0+1)位的最小幸运数.

情况二,n这个数大于n0位中最大的那个幸运数(相信各位dalao都会求),此时输出(n0+1)位的最小幸运数.

现在先把这两个特判的代码写出来:
```
	cin>>s;
	
	for(int i=0;i<s.size()/2;i++)t+='7';
	for(int i=0;i<s.size()/2;i++)t+='4';
	
	if(s.size()%2||s>t)
	{
		t="";
		
		for(int i=0;i<s.size()/2+1;i++)t+='4';
		for(int i=0;i<s.size()/2+1;i++)t+='7';
		
		cout<<t;return 0;
	}
```

（上述片段中,字符串s表示n,t表示n0位中最大的幸运数）

OK,现在我们可以保证答案就在n0位的数中.

下面就是DFS.

我们给DFS设置4个变量:
```
void DFS(int lvl,int x,int y,bool flag)
```
lvl:当前枚举到了第几位

x,y:统计当前4和7的个数

flag:剪枝用的,这里表示枚举的数是否已经大于n(具体干什么的我一会再说)

下面贴DFS的程序,具体操作步骤在注释里.

```cpp
void DFS(int lvl,int x,int y,bool flag)
{	
	if(x>s.size()/2||y>s.size()/2)return;  //当前枚举出的数中4和7如果已经超过了n0/2,就没有必要再继续搜索下去了 
	
	if(lvl==s.size()){ans=t;return;}  //到终点咯!把答案附上. 
	
	if(flag)  //如果当前数已经比n大了,那么后面肯定先放4再放7保证最小 
	{
		t[lvl]='4';  //放4 
		
		DFS(lvl+1,x+1,y,1);  //继续往下搜 
		
		if(ans!="")return;   //如果有了答案了就返回 
		
		t[lvl]='7';   //放7(此时是因为4放的个数超过一半了,只能放7)
		
		DFS(lvl+1,x,y+1,1);   //继续往下搜 
	}
	else
	{
		if('4'>=s[lvl]) //如果当前填的位4大于等于n的当前位,则可以填 
		{
			t[lvl]='4';
			
			DFS(lvl+1,x+1,y,'4'>s[lvl]); //如果我能保证在这一位上填的数大于n在这一位上的数,那我不管后面怎么填都会比n大,所以后面会把flag变为1 
			
			if(ans!="")return;  //有答案了,返回 
		}
		
		if('7'>=s[lvl])
		{
			t[lvl]='7';
			
			DFS(lvl+1,x,y+1,'7'>s[lvl]);
		}//意思和上面一样,只不过把4换成了7 
	}
}
```

现在来解释一下flag:

由于我是从第一位往最后一位搜的,那么如果我当前的这一位大于n的这一位,则不管后面怎么填,填的数都肯定比n大.所以flag可以剪枝.

最后贴完整AC代码:

```cpp
#include<bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define Unique(x) x.erase(unique(all(x)),x.end());

using namespace std;

const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};

const int Days[]={-1,31,28,31,30,31,30,31,31,30,31,30,31};

inline int read()
{
	#define gc getchar
	int ans=0;
	bool f=1;
	char ch=gc();
	
	while(!isdigit(ch))f^=ch=='-',ch=gc();
	
	while(isdigit(ch))ans=((ans<<2)+ans<<1)+(ch^48),ch=gc();
	
	return f?ans:-ans;
	
	#undef gc
}

typedef long long ll;

string s,t;
string ans;

void DFS(int lvl,int x,int y,bool flag)
{	
	if(x>s.size()/2||y>s.size()/2)return;
	
	if(lvl==s.size()){ans=t;return;}
	
	if(flag)
	{
		t[lvl]='4';
		
		DFS(lvl+1,x+1,y,1);
		
		if(ans!="")return;
		
		t[lvl]='7';
		
		DFS(lvl+1,x,y+1,1);
	}
	else
	{
		if('4'>=s[lvl])
		{
			t[lvl]='4';
			
			DFS(lvl+1,x+1,y,'4'>s[lvl]);
			
			if(ans!="")return;
		}
		
		if('7'>=s[lvl])
		{
			t[lvl]='7';
			
			DFS(lvl+1,x,y+1,'7'>s[lvl]);
		}
	}
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	
	cin>>s;
	
	for(int i=0;i<s.size()/2;i++)t+='7';
	for(int i=0;i<s.size()/2;i++)t+='4';
	
	if(s.size()%2||s>t)
	{
		t="";
		
		for(int i=0;i<s.size()/2+1;i++)t+='4';
		for(int i=0;i<s.size()/2+1;i++)t+='7';
		
		cout<<t;return 0;
	}
	
	t=s;
	
	DFS(0,0,0,0);
	
	cout<<ans;
	
	//printf("Time used = %.12f",(double)(clock())/CLOCKS_PER_SEC);
	return 0;
}
```

求过！求点赞！谢谢！

---

## 作者：thh_loser (赞：2)

# CF95B Lucky Numbers

[题目链接](https://www.luogu.com.cn/problem/CF95B)

# 题意
给出一个 $n$，构造出一个大于等于 $n$ 且仅由数量相等的 $4$、$7$ 的数。

# 思路
这道题其实是一道思路顺畅，但需要注意一些细节的模拟题。

首先观察题目要求，易得构造出来的数其实是偶数位的，因此我们可以进行第一个判断--如果是奇数位数就直接将位数加一，设加之前的位数为 $l$，则该情况输出 $\frac{(l+1)}{2}$ 个 $4$ 和 $7$。

其次，定义函数 $check$ 为在剩余位数填上最大值，能否比原数大，具体来说就是尽量先填 $7$ 再填 $4$。则有了第二个判断：开始时在第一位就开始判断，如果不能塞满则直接将 $l$ 加二，输出。

特判后就是模拟了，模拟前先引入一个标记 $flag$，用于判断当前是否已经一定大于 $n$。

考虑第 $i$ 位，假如 $n_{i}$ 比 $4$ 小，则该位一定为 $4$，且将 $flag$ 改为 $1$。

如果 $n_{i}$ 为 $4$ 则运用 $check$ 进行判断，如果可以则为 $4$，否则为 $7$，且将 $flag$ 改为 $1$。

最后由于之前的判断现在一定是能解得，因此填 $7$ 并对于 $n_{i}$ 小于 $7$ 的情况将 $flag$ 改为 $1$。

除了这些判断外，再储存已使用 $4$、$7$ 的数量，如果已达到 $\frac{l}{2}$ 则输出另一个。

该有如果 $flag$ 已经为 $1$，则尽量先填 $4$ 再填 $7$。

总的来说就是这样，这道题思维难度不是很大，但很考验思维的严谨程度。

# code
```c++14
#include<bits/stdc++.h>
using namespace std;
char n[100010];
int nl;
int si,qi;
bool dy;
void print(){
	for(int i=1;i<=nl/2;i++)cout<<4;
	for(int i=1;i<=nl/2;i++)cout<<7;
}
bool check(int x){//check函数 
	int re7=nl/2-qi;
	for(int i=x;i<=nl;i++){
		if(re7){
			if((n[i]-'0')<7)return 1;
			else if((n[i]-'0')>7)return 0;
			re7--;
		}
		else{
			if((n[i]-'0')<4)return 1;
			else if((n[i]-'0')>4)return 0;
		}
	}
	return 1;
}
int main(){
	cin>>n+1;
	nl=strlen(n+1);
	if(nl%2){//位数为奇数 
		nl++;
		print();
	}
	else if((n[1]-'0')>7||!check(1)){//在当前位数不能满足要求 
		nl+=2;
		print();
	}
	else{
		for(int i=1;i<=nl;i++){
			if(si==nl/2){
				cout<<7;
				qi++;
				continue;
			}
			if(qi==nl/2){//分别判断4 、7的 个数 
				cout<<4;
				si++;
				continue;
			}
			if(dy){//已经大于了 
				si++;
				cout<<4;
			}
			else{
				if((n[i]-'0')<4){					
					cout<<4;
					si++;
					dy=1;
				}
				else if((n[i]-'0')==4){
					if(check(i+1)){
						cout<<4;
						si++;
					}
					else{
						cout<<7;
						dy=1;
						qi++;
					}
				}
				else{
					cout<<7;
					qi++;
					if((n[i]-'0')<7)dy=1;
				}
			}
		}
	}
}
```

---

## 作者：_Lazy_zhr_ (赞：1)

这里使用递归的方式实现。

我们设给出的字符串长度为 $len$。

如果 $len \bmod 2 = 1$，由于不可能出现长度为奇数的超级幸运数字，所以直接输出一个长度为 $len+1$ 的字符串，其中前 $\frac{(len+1)}{2}$ 个字符为 $4$，后 $\frac{(len+1)}{2}$ 个字符为 $7$。

代码如下：

```cpp
for(int i=0;i<=len;i++)
	if(i<=len/2) cout<<4;
	else cout<<7;
```

如果 $len \bmod 2 = 0$，先尝试构造长度为 $len$ 的答案，代码如下：

```cpp
int len,ans[100005];
string s;
bool x,maxn;
void dfs(int _4,int _7,int step){
	if(x) exit(0);
	if(step==len){
		for(int i=0;i<len;i++) cout<<ans[i];
		x=true;
		exit(0);
	}
	if(maxn){
		if(_4<len/2){
			ans[step]=4;
			dfs(_4+1,_7,step+1);
		}
		else{
			ans[step]=7;
			dfs(_4,_7+1,step+1);
		}
	}
	else if(s[step]>'7') return ;
	else if(s[step]>'4'){
		if(_7==len/2) return ;
		if(s[step]<'7') maxn=true;
		ans[step]=7;
		dfs(_4,_7+1,step+1);
	}
	else{
		if(_4<len/2){
			if(s[step]<'4') maxn=true;
			ans[step]=4;
			dfs(_4+1,_7,step+1);
			if(x) exit(0);
		}
		if(_7==len/2) return ;
		maxn=true;
		ans[step]=7;
		dfs(_4,_7+1,step+1);
	}
	if(x) exit(0);
}
```

 `_4` 表示当前 $4$ 的出现次数，`_7` 表示当前数字 $7$ 的出现次数，`step` 表示枚举到了第 $step$ 位，`x` 表示答案已经输出过了。

如果枚举完了，就直接输出，然后 `exit(0)`。

如果前面已经有填的数比给出的字符串的数大，这一位就直接填 $4$，不过如果 $4$ 已经填了 $\frac{len}{2}$ 个了，就得填 $7$。

这里“前面已经有填的数比给出的字符串的数大”是什么意思呢？举个例子：假设给的字符串为 `1888`，第一位可以填 $4$，在第二位中，虽然 $4<8$，但这一位还是可以填 $4$，因为“前面已经有填的数比给出的字符串的数大”。

前面的都是特殊情况，接下来就根据 `s[step]` 的值来递归。

这里讲一个重点，就是 `s[step]<='4'` 的情况。如果能填 $4$，那么先试着填 $4$。填 $4$ 不成就填 $7$。

最后，若无法构造出长度为 $len$ 的答案，就输出一个长度为 $len+2$ 的答案，其中前 $\frac{(len+2)}{2}$ 个字符为 $4$，后 $\frac{(len+2)}{2}$ 个字符为 $7$。

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int len,ans[100005];
string s;
bool x,maxn;
void dfs(int _4,int _7,int step){
   	if(x) exit(0);
   	if(step==len){
   		for(int i=0;i<len;i++) cout<<ans[i];
    	x=true;
    	exit(0);
    }
    if(maxn){
    	if(_4<len/2){
    		ans[step]=4;
    		dfs(_4+1,_7,step+1);
    	}
    	else{
    		ans[step]=7;
    		dfs(_4,_7+1,step+1);
    	}
    }
    else if(s[step]>'7') return ;
    else if(s[step]>'4'){
    	if(_7==len/2) return ;
    	if(s[step]<'7') maxn=true;
    	ans[step]=7;
    	dfs(_4,_7+1,step+1);
    }
    else{
    	if(_4<len/2){
    		if(s[step]<'4') maxn=true;
    		ans[step]=4;
    		dfs(_4+1,_7,step+1);
    		if(x) exit(0);
    	}
   		if(_7==len/2) return ;
    	maxn=true;
   		ans[step]=7;
    	dfs(_4,_7+1,step+1);
   	}
   	if(x) exit(0);
}
void solve(){
   	cin>>s;
   	len=s.size();
   	if(len%2){
   		for(int i=0;i<=len;i++)
   			if(i<=len/2) cout<<4;
   			else cout<<7;
   		return ;
   	}
   	else{
   		dfs(0,0,0);
   		if(!x){
   			for(int i=-1;i<=len;i++)
   				if(i<len/2) cout<<4;
   				else cout<<7;
   		}
   	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--) solve();
    return 0;
}
```

谢谢观看！

---

## 作者：Erica_N_Contina (赞：1)

## 题意

给出一个 $≤10^5$ 位的数字 $n$，求不小于它的幸运数字。

幸运数字的定义是数字中只有 $4,7$ 且 $4$ 的数量与 $7$ 相同。

## 思路

结合题意，很显然当 $n$ 的长度 $len$ 为奇数时，我们只能找到长度为 $len+1$ 的最小的幸运数字作为答案。

当 $len$ 为偶数时，我们只好搜索下去了。

我们用 `dfs(x,cnt1,cnt0,up)` 来表示当前要填第 $x$ 个数字，已经用了 $cnt1$ 个 $7$，$cnt0$ 个 $4$。因为我们还需要考虑到进位的问题，所以我们需要用 $up$ 来传递一下。

当我们枚举到一个数位 $i$ 时，我们能放 $4$ 的就放 $4$，否则放 $7$，或者判不成立：

- 如果 $n_i<4$，则该位填 $4$，$up$ 置 $1$。

- 如果 $n_i=4$，则该位填 $4$。

- 如果 $4<n_i<7$，则该位填 $7$，$up$ 置 1。

- 如果 $n_i=7$，则该位填 $7$。

- 如果 $n_i>7$，如果 $up=1$ 则置 $4$，否则 `return`。

这是所有的情况了。代码中我们可以合并一些情况。如果我们通过 dfs 没办法找到答案（例如数字 $9999$），那么我们只能按奇数 $len$ 的情况来输出了，输出长度为 $len+2$ 的最小幸运数字。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////
#pragma GCC optimize(3)
//
#include<bits/stdc++.h>

//
//#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back


using namespace std;
//
const int N=1e6+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
//const int IINF=1e18;
const db eps=1e-9;
//
int m,b,q,op,idx,len,ans[N],id[N];

string n;

bool dfs(int u, int cnt0, int cnt1,int up) {
	if (cnt0 > len /2 || cnt1 > len /2) return 0;
	if (u == len) {
		for (int i=0;i<len;i++)
			cout<<ans[i];
		exit(0);
	}
	n[u]-='0';
	if(n[u]<=4||up){//能用4的就用4
		ans[u]=4;
		if(dfs(u+1,cnt0+1,cnt1,up||(n[u]<4))){
			return 1;
		}
	}
	if(n[u]<=7||up){
		ans[u]=7;
		if(dfs(u+1,cnt0,cnt1+1,up||(n[u]<7))){
			return 1;
		}
	}
	return 0;
}
void lucnum(int n){
	for(int i=1;i<=n/2;i++)cout<<4;
	for(int i=1;i<=n/2;i++)cout<<7;
}
signed main(){
//	cin>>n>>m;
	cin>>n;
	len=n.size();
	
	if(len%2){
		lucnum(len+1);
		return 0;
	}
//	cerr<<"len="<<len<<endl;
	dfs(0,0,0,0);
	lucnum(len+2);
	
}
//

```

记 $100$ 篇博文。




---

## 作者：Link_Cut_Y (赞：1)

小清新~~爆搜题~~。

可以从下面几个方面来分类讨论：

 - $n$ 为奇数
 
 如果长度为 $n$ 无论如何 $4$ 和 $7$ 的个数都不可能相等了。因此只能构造 $n + 1$ 位的幸运数。构造方案：前一半填 $4$，后一半填 $7$。
 
 - $n$ 为偶数
 
 爆搜。设 `dfs(u, cnt0, cnt1, flag)` 表示当前要填第 $u$ 位，当前 $4$ 的个数为  $cnt_0$，$7$ 的个数为 $cnt_1$。$flag$ 当前是否有限制。没有限制是指前面某一位已经超过上限，有限制是指前面每一位都等于可以填的上界。爆搜时能填 $4$ 就填 $4$，不能填 $4$ 就填 $7$。
 
 - 仍然搜不到答案
 
 那么构造位数 $n + 2$ 的方案。构造方法和 $n$ 为奇数的情况一样。
 
大概是最短代码了。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 100010;
char s[N];
int n, ans[N];

void special_sub(int n) {
	for (int i = 1; i <= n; i ++ )
		printf("%d", (i > n >> 1) ? 7 : 4);
}
bool dfs(int u, int cnt0, int cnt1, bool ok) {
	if (cnt0 > n >> 1 or cnt1 > n >> 1) return false;
	if (u == n + 1) {
		for (int i = 1; i <= n; i ++ )
			printf("%d", ans[i]);
		return true;
	}
	if (s[u] <= '4' or ok)
		if (ans[u] = 4, dfs(u + 1, cnt0 + 1, cnt1, ok | (s[u] < '4'))) return true;
	if (s[u] <= '7' or ok)
		if (ans[u] = 7, dfs(u + 1, cnt0, cnt1 + 1, ok | (s[u] < '7'))) return true;
	return false;
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	special_sub(((n & 1) ? n + 1 : 
	            (!dfs(1, 0, 0, 0) ? n + 2 : 0)));
	return 0;
}
```

---

## 作者：FReQuenter (赞：1)

## 思路

当 $n$ 有奇数位时，因为一个 Lucky Number 一定有偶数位，所以答案比 $n$ 多一位，那么任何比 $n$ 多一位的 Lucky Number 都比 $n$ 大，所以答案形如 $4\cdots47\cdots7$，总长为 $n$ 的位数加一，$4$ 和 $7$ 的数量同样多。

接下来讨论 $n$ 有偶数位时：

如果 $n$ 大于和 $n$ 位数相同的最大的 Lucky Number（形如 $7\cdots74\cdots4$），则答案的位数一定比 $n$ 多。因为 $n$ 有偶数位，答案也是偶数位，所以答案有 $n+2$ 位。答案位数比 $n$ 多，显然要尽量小。形如 $4\cdots47\cdots7$。

其它情况下，就要一位一位判断填 $4$ 还是 $7$。继续分类：

如果之前有一位已经大于 $n$ 那一位，那这个 Lucky Number 已经比 $n$ 大了。那么之后越小越好，先把 $4$ 用完，剩下用 $7$。

如果之前所有位和 $n$ 都一样，继续分类：

当前位如果是 $4$，那要检查如果直接填 $4$，后面的如果填成 $7...74...4$ 是否比 $n$ 的后面部分大或一样，那么填 $4$，否则填 $7$。

否则，优先填 $4$，如果当前位比 $4$ 大或没有 $4$ 了就填 $7$。

代码不难写，但可能比较长，注意细节。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool les(string a,string b){
    if(a.length()!=b.length()) return a.length()<b.length();
    return a<b;
}
signed main(){
    string n;
    cin>>n;
    int s4=n.length();
    s4++,s4/=2;
    int s7=s4;
    //cout<<s4<<' '<<s7<<'\n';
    string pre="";
    int ss4=s4,ss7=s7;
    while(s4--) pre+='4';
    while(s7--) pre+='7';
    if((int)n.length()&1){//偶数位
        cout<<pre;
        return 0;
    }
    s4=ss4,s7=ss7;
    reverse(pre.begin(),pre.end());
    if(les(pre,n)){
        reverse(pre.begin(),pre.end());
        pre="4"+pre+"7";//再加两位
        cout<<pre;
        return 0;
    }
    else{
        string tmp=n;
        bool f=false;//之前是否有某一位比n的那一位大
        for(int i=0;i<(int)n.length();i++){
            //cout<<'['<<s4<<' '<<s7<<']'<<'\n';
            if(f){//之前有某一位比n的那一位大
                if(s4){//优先填4
                    s4--;
                    cout<<4;
                }
                else{
                    s7--;
                    cout<<7;
                }
            }
            else if(n[i]!='4'&&n[i]!='7'){
                f=true;
                if(n[i]<'4'){//比4小
                    if(s4){//4优先
                        s4--;
                        cout<<4;
                        pre.erase(pre.begin()+pre.length()-1);
                        tmp.erase(tmp.begin());
                    }
                    else{
                        s7--;
                        cout<<7;
                        pre.erase(pre.begin());
                        tmp.erase(tmp.begin());
                    }
                }
                else if(n[i]<'7'){//比4大，比7小，填4
                    s7--;
                    cout<<7;
                    pre.erase(pre.begin());
                    tmp.erase(tmp.begin());
                }
                else{
                    //运行不到这里的，运行到这里你就写挂了
                    cout<<"Something happend... by FReQuenter,do not copy it!";
                    exit(1);
                }
            }
            else{
                if(n[i]=='4'){//如果是4
                    if(s4&&pre.substr(0,pre.length()-1)>=tmp.substr(1,tmp.length()-1)){
                        s4--;//检查是否合法，优先填4
                        cout<<4;
                        pre.erase(pre.begin()+pre.length()-1);
                        tmp.erase(tmp.begin());
                    }
                    else{
                        f=true;//7比4大
                        s7--;
                        cout<<7;
                        pre.erase(pre.begin());
                        tmp.erase(tmp.begin());
                    }
                }
                else{
                    s7--;
                    cout<<7;
                    pre.erase(pre.begin());
                    tmp.erase(tmp.begin());
                }
            }
            //cout<<'['<<s4<<' '<<s7<<']'<<'\n'<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：jzjr (赞：0)

# 数位 DP—Lucky Numbers

[题目传送门](https://www.luogu.com.cn/problem/CF95B)

## 题目翻译：

定义 Lucky Numbers 为只有 $4,7$ 两个字符组成的数字，****并且 $4,7$ 两个字码出现次数相同****；

现在给你一个正整数，请你求出大于等于这个数的最小的 Lucky Numbers；

## 解法

记输入字符串 $k$ 长度为 $l$；

考虑两种情况：

### 情况一：$l$ 为奇数

由这句话：

> 当一个十进制幸运数字中含有 $4$ 和 $7$ 的数量相同时；


这里有一个隐含的条件：答案长为偶数；

那么考虑最小的数长度一定是 $l+1$；

而此时没有了大小的限制，可以直接贪心：

前 $(\frac{l}{2}+1)$ 个 $4+$ 后  $(\frac{l}{2}+1)$ 个 $7$；

输出即可：

```cpp
l=k.size();
if(l%2==1){
	for(int i=1;i<=l/2+1;i++)printf("4");
	for(int i=1;i<=l/2+1;i++)printf("7");
	return 0;
}
```

### $l$ 为偶数

此时貌似就可以暴力枚举了，

但是这样的时间复杂度是 $O(2^l)$；

直接 $T$ 飞；

显然：考虑数位 DP，

但是授人以鱼不如授人以渔；

#### 什么是数位 DP

数位 DP 是一种利用类似 DP 的记忆化搜索方法，与在狭义上的 DP，即最优化问题有一定区别，用于解决计数以及求和问题。—— [OIWIKI](http://oiwiki.com/dp/count/)

而数位 DP 一般复赛直接考的不多，反而是初赛或者夹着其他东西一起考的比较多；

这都是因为数位 DP 的模版性；

他的具体实现思路如下：

从后往前（也可以从前往后）依次枚举数位，

利用记忆化搜索和剪枝来实现时间上的优化；

同时也可以通过记忆化搜索实现计数的快速求解；

而一个数位 DP 的深度优先搜索往往需要很多的状态变量，因该视情况而定，而不是一味的套模版，这样会造成变量的冗长导致状态数量和转移时间的不是最优；

而这种情况只需要多练即可解决；

下面是代码模版：

```cpp
int dfs(int pos,int milit,int zero(是否有前导0),int other(其他变量)){
  //其中，pos 表示当前数位， milit 表示是否有数字大小限制；
  //zero 表示是否有前导 0,other 为其他变量；
	if(pos<=0)return ans;//枚举结束，返回当前答案；
  	if(!milit&&zero&&dp[pos][other]!=-1)return dp[pos][other];//记忆化搜索的返回；
  	int cnt=9;
  	if(milit)cnt=a[pos];//是否有限制
  	int met=0;//记录答案的
  	for(int i=0;i<=cnt){
    		if(i==asd)continue;//剪枝的实现
      		met+=dfs(pos+1,milit&(i==cnt),zero||(i!=0),other);//求和
    	}
  	if(!milit&&zero)dp[pos][other]=met;//记忆化搜索的记录答案；
  	return met;
}
```

#### 回归本题；

本题不用计数，只需要按位枚举即可；

记得剪枝+限制；

那么我们就能得到如下代码：

```cpp
int a[100001],l;
void dfs(int pos,int dig4,int dig7,int milit,string num){
	if(dig4>l/2||dig7>l/2)return ;//剪枝
	if(num>ans)return ;//剪枝
	if(pos>=l){ans=num;return ;}//记录当前最优答案；
	int cnt=0;
	if(milit)cnt=a[pos];//限制
	if(cnt<=4)dfs(pos+1,dig4+1,dig7,milit&(cnt==4),num+'4');//转移，下一位为 4
	if(cnt<=7)dfs(pos+1,dig4,dig7+1,milit&(cnt==7),num+'7');//转移，下一位为 7
}
void part(){//初始化
	string asd="";
	for(int i=0;i<l;i++)a[i]=k[i]-'0';
	dfs(0,0,0,1,asd);
}
```

同时注意当前长度没有答案时的贪心，

注意初始化字符串 ans；

那么代码也是呼之欲出了；

## AC code：

```cpp
#include<bit/stdc++.h>
using namespace std;
string ans="",k;
int a[100001],l;
void dfs(int pos,int dig4,int dig7,int milit,string num){
	if(dig4>l/2||dig7>l/2)return ;
	if(num>ans)return ;
	if(pos>=l){ans=num;return ;}
	int cnt=0;
	if(milit)cnt=a[pos];
	if(cnt<=4)dfs(pos+1,dig4+1,dig7,milit&(cnt==4),num+'4');
	if(cnt<=7)dfs(pos+1,dig4,dig7+1,milit&(cnt==7),num+'7');
}
void part(){
	string asd="";
	for(int i=0;i<l;i++)a[i]=k[i]-'0';
	dfs(0,0,0,1,asd);
}
int mian (){
	cin>>k;
	l=k.size();
	if(l%2==1){
		for(int i=1;i<=l/2+1;i++)printf("4");
		for(int i=1;i<=l/2+1;i++)printf("7");
		return 0;
	}
	for(int i=0;i<l;i++)ans+='9';
	string asd=ans;
	part(k);
	if(asd==ans){
		for(int i=1;i<=l/2+1;i++)printf("4");
		for(int i=1;i<=l/2+1;i++)printf("7");
		return 0;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：dutianchen1 (赞：0)

# CF95B Lucky Numbers

# 思路简析

首先，对于位数为奇数的的数字，显然我们所求的数的位数比其多一位。而且答案数字显然前一半为 $4$ 后一半为 $7$。直接输出即可

对于位数为偶数的数字，我们考虑对每一位进行搜索。搜索条件如下：

- 当前 $4$ 的个数与 $7$ 的个数都为 $\frac{len}{2}$ 时，直接输出并直接结束。
- 当前 $4$ 的个数小于 $\frac{len}{2}$ 且已经放好的之前位置的数已经大于所要求的数（也就是说此处可以随便填数）或当前位置的数小于 $4$，则将当前位置记为 $4$ 并向下继续搜索。
- 当前 $7$ 的个数小于 $\frac{len}{2}$ 且已经放好的之前位置的数已经大于所要求的数（也就是说此处可以随便填数）或当前位置的数小于 $7$，则将当前位置记为 $7$ 并向下继续搜索。

除了以上三点，还有一点对于偶数位数的特判：

当某一位该放 $4$ 或 $7$ 时，因为小于原数而不能放下时，我们只能延长两位从而满足条件。

---
代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
char ans[N];
string S;
int len;
void dfs(int len,int cnt4,int cnt7,int l,bool flag) {
	if(cnt4==len/2&&cnt7==len/2)
	{
		for(int i=0;i<l;i++)cout<<ans[i];
		exit(0);
	}
	if(cnt4<len/2&&(flag||S[l]<='4'))
	{
		ans[l]='4';
		dfs(len,cnt4+1,cnt7,l+1,(flag||S[l]<'4'));
	}
	if(cnt7<len/2&&(flag||S[l]<='7'))
	{
		ans[l]='7';
		dfs(len,cnt4,cnt7+1,l+1,(flag||S[l]<'7'));
	}
}
bool flag;
int main()
{
	cin>>S;
	len=S.size();
	if(len&1){
		len++;
		flag=true;	
	}

	if(!flag)
	{
		dfs(len,0,0,0,0);
		len+=2;
		for(int i=0;i<len/2;i++)cout<<4;
		for(int i=0;i<len/2;i++)cout<<7;
	}
	else{
		for(int i=0;i<len/2;i++)cout<<4;
		for(int i=0;i<len/2;i++)cout<<7;
	}

	return 0;	
} 
```

---

## 作者：Herowin (赞：0)

给一个当前我认为最简单的写法。

首先我们想到当一个数是单数位时，在当前数位的情况下必定没有解。

例:$44777$ 无论如何也不能让这个数满足题意，所以最小的答案必定是$444777$也就是位数加$1$,贪心的先放4。再放7。

还可以想到若是最前面的一位数$>7$,不就一定没有在当前位数的解了吗?

例：$778444$ 答案是$44447777$

所以对于需要增加位数的情况我们只需要判一下单复数，和有没有超过当前位数的最大答案（注：最大答案是先放七）

接下来对于当前位数一定有答案的情况来说呢? 首先可以想到我们进行一次$O(n)$的遍历($n = strlen (ch)$) 若当前位数出现了非$4/7$的数，直接把他变成$4/7$（大于七的话，也仅仅只是需要找到前面的一个四变成七，然后return掉），另一种情况便是当前含有的$4/7$已经超过了$n/2$ ，对于4超过的情况只需要把他以及后面的数字都变成7就可，对于$7$超过的情况就是找到前面的一个$4$换成$7$即可。（友情提示：一定要是$num(7) == n / 2$ 之前的$4$,不然你会在第52个点疯狂WA）

$emmmm$, 这道题是一道非常注意细节的题，思路倒是不难想，难点在于如何保证正确的情况下写出简短的代码。

给出代码
```cpp

#include <bits/stdc++.h>
using namespace std ;
const int N = 100024 ;
char ch[N] ;
int ans[N] , c[10] , newwpos ;
bool found ;
bool check (int Nn) {
	for (int i = 1 ; i <= Nn ; i ++) {
		int nownum = ch[i] - '0' , nowmost = i <= Nn / 2 ? 7 : 4 ;
		if (nownum == nowmost) continue ;
		else if (nownum > nowmost) return false ;
		else return true ;
	}
	return true ;
}
int main () {
	scanf ("%s" , ch + 1) ;
	int n = strlen (ch + 1) ;
	if (n % 2 == 1 || !check (n)) {
		n += n % 2 ? 1 : 2 ;
		for (int i = 1 ; i <= n ; i ++) cout << (i <= n / 2 ? 4 : 7) ;	
		return 0 ;
	}
	int bef = -1 , newwpos = n ;
	for (int i = 1 ; i <= n ; i ++) {
		int nownum = ch[i] - '0' ;
		if (nownum == 7 || nownum == 4) c[ans[i] = nownum]++ , bef = (ans[i] == 4 && !found ? i : bef) ;
		else if (nownum < 7 && nownum != 4) ans[i] = nownum < 4 ? 4 : 7 , c[ans[i]] ++ , newwpos = i , bef = (ans[i] == 4 && found ? i : bef) ;
		if (c[4] > n / 2) newwpos = i , ans[newwpos] = 7 ;
		else if (c[7] == n / 2) found = 1 ;
		else if (c[7] > n / 2 || nownum > 7) newwpos = bef , ans[newwpos] = 7 ;
		if (newwpos != n) break ;
	}
	c[4] = 0 , c[7] = 0 ;
	for (int i = 1 ; i <= newwpos ; i ++) {cout << ans[i] ; c[ans[i]] ++ ;}
	for (int i = 1 ; i <= (n / 2) - c[4] ; i ++) cout << 4 ;
	for (int i = 1 ; i <= (n / 2) - c[7] ; i ++) cout << 7 ; 
	return 0 ;
}




```


---

