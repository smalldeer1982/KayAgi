# Median String

## 题目描述

给定两个字符串 $s$ 和 $t$，它们都由恰好 $k$ 个小写拉丁字母组成，且 $s$ 的字典序严格小于 $t$。

我们考虑所有长度为 $k$ 的小写拉丁字母字符串中，字典序不小于 $s$ 且不大于 $t$（包括 $s$ 和 $t$）的字符串，按字典序排列。例如，当 $k=2$，$s=$"az"，$t=$"bf" 时，所有满足条件的字符串为 \["az", "ba", "bb", "bc", "bd", "be", "bf"\]。

你的任务是输出这个列表的中位数（即中间的元素）。对于上面的例子，中位数是 "bc"。

保证满足条件的字符串个数是奇数。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
az
bf
```

### 输出

```
bc
```

## 样例 #2

### 输入

```
5
afogk
asdji
```

### 输出

```
alvuw
```

## 样例 #3

### 输入

```
6
nijfvj
tvqhwp
```

### 输出

```
qoztvz
```

# 题解

## 作者：Deft_t (赞：6)

# 思路
因为字符串中只有小写字母，因此可以把两个字符串看成 $26$ 进制高精度数 $a$ 和 $b$ 。答案就是 $(a+b)/2$ 。  
这个式子可以从高位往低位同时计算高精度加法和高精度对低精度的除法。  
具体思路见代码注释。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005],t[200005];
int a[200005],b[200005];
int ans[200005];
int main()
{
	int k;
	scanf("%d%s%s",&k,s,t);
	for(int i = 0;i < k;i++) a[i] = s[i]-'a',b[i] = t[i] - 'a';//转26进制数值分别存到数组a和数组b中 
	int c = 0; //记录向低位的进位 
	for(int i = 0;i < k;i++){
		ans[i] = (a[i] + b[i] + c) / 2;//同时做加法和除法 
		int j = i;
		while(ans[j] >= 26){  //因为c的存在，相加后除以2的结果可能会大于或等于26，此时就需要向高位进位 
			ans[j - 1]++;
			ans[j] -= 26;
			j--;
		}
		if((a[i] + b[i]) & 1) c = 26; //如果和是奇数不能整除，当前位向下取整多减了1，相当于低一位加了26 
		else c = 0;
	}
	for(int i = 0;i < k;i++) printf("%c",(char)('a' + ans[i]));
	return 0;
}


```


---

## 作者：Twig_K (赞：4)

【高精度】【26进制】

如果给你一串数：

**1,2,3,4,5,6……**

怎么求 $a$ 和 $b$ 之间最中间的数 $mid$ ？

$mid=\frac{a+b}{2}$

---

那么根据字符串排列的单调性，如果想求字符串 $s$ 和 $t$ 之间，最中间的字符串便是 $s$ 的序号与 $t$ 的序号之间的平均值。

$s$ 和 $t$ 的序号分别用 $26$ 进制数来存储。

再观察数据范围：$k≤2\times10^5$ ，用高精度实现。

-----

需要注意的点：

1.前导零的判断

2.进位和退位

---

注释版代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+20;

int k;
string s,t;
int ss[maxn],tt[maxn];
int aa[maxn],bb[maxn];

signed main()
{
	cin>>k>>s>>t;
   //转化为26进制数，每一位存在对应数组下标处，高精度倒序存储。
	for(int i=0;i<k;i++) ss[k-i]=s[i]-'a',tt[k-i]=t[i]-'a';
   //aa数组存放头尾之和
	for(int i=1;i<=k;i++)
	{
		aa[i]+=ss[i]+tt[i];
		aa[i+1]+=aa[i]/26;
		aa[i]%=26;
	}
   //将头尾之和除以二即是中间值，sht和flag的作用是判断前导零
	int sht=k+1,x=0;
	bool flag=1;
	for(int i=k+1;i>=1;i--)
	{
		int tmp=x*26+aa[i];
		if(tmp<2){
			if(flag) sht--;
			x=tmp;
		}
		flag=0;
		bb[i]=tmp/2; x=tmp%2;
	}
    //重新转成小写字母输出
	for(int i=sht;i>=1;i--) cout<<char(bb[i]+'a');
	return 0;
}
```

---

## 作者：OLE_OIer (赞：2)

思路就是将字符串转为 26 进制数，然后用高精度加法和高精度除以单精度的算法就可以求解。

话不多说，给大佬们献上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ln;
struct BIG{
	string s;
	long long x[200010];
	int len;
   /*从字符串转化为26进制数*/
	void change(){
		cin>>s;
		len=s.length();
		for(int i=1;i<=len;++i) x[len-i+1]=s[i-1]-'a';
	}
	void print(){
      /*重点来了，题目让输出ln位，就要输出ln位*/
		for(int i=ln;i>0;--i) cout<<char(x[i]+'a');
	}
     /*高精度加法*/
		BIG operator+(const BIG &a){
		BIG c;
		c.len=max(len,a.len);
		int u=0;
		for(int i=1;i<=c.len;++i){
			int t=u;
			if(i<=a.len) t+=a.x[i];
			if(i<=len) t+=x[i];
			c.x[i]=t%26;
			u=t/26;
		}
		if(u>0) c.x[++c.len]=u;
		return c;
	}
       	/*高精度除以单精度*/
	BIG operator/(const int a){
		BIG c;
		c.len=len;
		int tmp=0;
		for(int i=c.len;i>0;--i){
			long long r=(long long)26*tmp+x[i];
			c.x[i]=r/a;
			tmp=r%a;
		}
		while(!c.x[c.len]&&c.len>1) --c.len;
		return c;
	}
};
BIG x,y; 
int main(){
	cin>>ln;
	x.change();
   y.change();
	BIG c=x+y;
	c=c/2;
	c.print();
	return 0;
} 
   //求管理员大大给过
```

---

## 作者：liruixiong0101 (赞：1)

## P0 前置知识：
高精度。

## P1 题意：
给你两个长度为 $k$ 的字符串，让你求出这在这两个字符串字典序中间的最中间的数。

## P2 思路：
如果把字符串改为整数，是不是这道题就变得很简单了呢？  
答案就是 $\frac{a+b}{2}$。

---

将这题的 $a,b$ 从整数换成字符串就是将 $a,b$ 变成了 $26$ 进制的高精度数了，然后就模拟高精度即可。

## P3 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 2e5 + 5;
int n;
int a[kMaxN], b[kMaxN], c[kMaxN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    char ch;
    cin >> ch;
    a[i] = ch - 'a';
  }  // 转化成26进制数
  for (int i = 1; i <= n; i++) {
    char ch;
    cin >> ch;
    b[i] = ch - 'a';
  }  // 另一个字符串也要要转化成26进制数
  for (int i = n; i >= 1; i--) {
    c[i] += a[i] + b[i];
    c[i - 1] += c[i] / 26;
    c[i] %= 26;
  }                           // 高精度加法
  int s = 1;                  // 看是否有进位的指针
  if (c[0]) s--;              // 看是否有进位
  fill(a + s, a + 1 + n, 0);  // 清空数组
  for (int i = s; i <= n; i++) {
    a[i] = c[i] / 2;
    c[i + 1] += c[i] % 2 * 26;
  }  // 高精度除法
  for (int i = 1; i <= n; i++) {
    cout << (char)(a[i] + 'a');
  }
  return 0;
}
```

## P4 AC 链接：
<https://codeforces.com/problemset/submission/1144/209764107>

---

## 作者：金霸王电池 (赞：1)

这道题的题意就是构造 S 和 T 两个字符串中间的所有字符串

（按字典序从小到大排列），然后输出中间那个字符串。  

首先我们把字母替换成数字，举个例子：

S = 11,T = 19.

则中间的所有数（字符串）为：

11，12，13，14，15，16，17，18，19.

最中间的数是 15.

发现什么规律了吗？15 就是 11 和 19 的平均数。

现在我们回到原题。按照上面的思路，我们可以把字符串换

成一个 26 进制的数（a 对应 0，b 对应 1，......,z 对应 25），

然后求平均数，再转换成字符串输出。

AC 代码：

```cpp
#include<bits/stdc++.h>//懒人专用万能头
using namespace std;
int n,aa[200010],bb[200010],cc[200010];
//aa , bb 代表转换过的 26 进制数, cc 是结果
string a,b;
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		aa[i]=a[i-1]-'a';
		bb[i]=b[i-1]-'a';//转换为 26 进制数
	}
	for(int i=n;i>=1;i--){
		cc[i]=cc[i]+aa[i]+bb[i];
		if(cc[i]>=26){
			cc[i]-=26;
			cc[i-1]++;
		}//加和
	}
	if(cc[0])//讨论位数
		for(int i=0;i<=n;i++){
			int mod=cc[i]%2;
			cc[i]/=2;
			cc[i+1]+=26*mod;//求平均数
		}
	else
		for(int i=1;i<=n;i++){
			int mod=cc[i]%2;
			cc[i]/=2;
			cc[i+1]+=26*mod;
		}
	for(int i=1;i<=n;i++)cout<<(char)(cc[i]+'a');
   //转换为字符串输出
	return 0;
} 
```



---

## 作者：limuloo (赞：1)

把字符串看成26进制的数（a对应0 b对应1 .. z对应25）

然后这道题无非就是把两个26进制的数相加，然后除以2就可以得到结果了

具体看代码
```cpp
#include <cstdio>
#define N 200005
int n;
char s1[N],s2[N];
int ans[N];

int main(){
	scanf("%d",&n);
	scanf("%s",s1);
	scanf("%s",s2);
	for(int i=n-1;i;i--){
		ans[i]+=(s1[i]-'a'+s2[i]-'a');
		ans[i-1]+=ans[i]/26;
		if(ans[i]>=26) ans[i]-=26;
	}
	ans[0]+=(s1[0]+s2[0]-'a'-'a');//先把两个26进制数的相加和求下来
	//for(int i=0;i<n;i++) printf("%d ",ans[i]);  printf("\n");
	for(int i=0;i<n;i++){
		if(ans[i]&1) ans[i+1]+=26;
		ans[i]/=2;
	}//除以2 注意如果当前位是奇数 除以2的时候要给低位加26（不难理解吧）
	for(int i=0;i<n;i++) printf("%c",ans[i]+'a'); printf("\n");
	return 0;
}
```



---

## 作者：—维尼— (赞：0)

## 题目描述
给定相同长度的两个字符串，找出两个字符串中间排列的所有序列中位于中间的字符串

就是把两个串中间的字典序排列搞出来，再输出中间的那个
## 解题思路

刚开始我还想着能不能用`next_permutation`更快搞出来，结果发现这和朴素的排列没半毛钱关系

其实我们可以换个思路，直接暴力求出中间值，所以我们要把字母转化为数字，也就是26进制数，从char数组中转移到int数组中

但是我们突然看到了数据范围

$k\le2*10^5$		

$k$就是字符串的长度
这就意味着我们要加入一个重要的东西：高精

高精都懂吧，不懂可以去看[——》模板《——](https://www.luogu.com.cn/problem/P1601)


当然这里用到的是弱化版的，普通的 高精减 和 高精除低精（就是/2啦）
之后看代码

## 代码简单又好懂

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005],t[200005],yy[200005]; 
int x[200005],y[200005],cha[200005],ans[200005];
//char num[30]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int main(){
//	freopen("midstr.in","r",stdin);
//	freopen("midstr.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=n;i++){
		cin>>t[i];
	}
	for(int i=1;i<=n;i++){
		x[i]=s[i]-'a';
		y[i]=t[i]-'a';
		yy[i]=t[i]-'a'; 
	}
	for(int i=n;i>=1;i--){
		if(y[i]>=x[i]){
			cha[i]=y[i]-x[i];
		}
		else{
			y[i-1]--;
			y[i]+=26;
			cha[i]=y[i]-x[i];
		}
	}
	int q;
	for(int i=1;i<=n;i++){
		q=cha[i]%2;
		cha[i]/=2;
		if(q!=0)
		cha[i+1]+=(q*26);
	}
	for(int i=n;i>=1;i--){
		if(yy[i]<cha[i])
		{
			yy[i-1]--;
			yy[i]=yy[i]+26;
		}
		ans[i]=yy[i]-cha[i];
	}
	for(int i=1;i<=n;i++)
    	cout<<(char)(ans[i]+'a');
	return 0;
}
```



---

## 作者：RainFestival (赞：0)

这道题目看起来很烦

考虑给每一个字符串一个编号

先将两个字符串看成 $26$ 进制数

然后相加即可

然后 $/2$ 即可

然后就非常简单

代码：

```cpp
#include<cstdio>
#include<cctype>
int n,a[200005],b[200005],c[200005],d[200005];
char get(){char ch;return isalpha(ch=getchar())?ch:get();}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) a[i]=get()-97;
	for (int i=1;i<=n;i++) b[i]=get()-97;
	int x=0;
	for (int i=n;i>=0;i--)
	{
		c[i]=(a[i]+b[i]+x)%26;
		x=(a[i]+b[i]+x)/26;
	}
	x=0;
	for (int i=0;i<=n;i++)
	{
		d[i]=(c[i]+26*x)/2;
		x=c[i]%2;
	}
	for (int i=1;i<=n;i++) putchar(d[i]+97);
	puts("");
	return 0;
}
```

---

## 作者：fanfansann (赞：0)

# $E.\ Median\ String$

$Description$

给定长度为k的字符串s和t，保证s的字典序小于t。现有一个字典序单调递增的序列，其中所有的字符串长度都是k，字典序满足大于等于s且小于等于t。求出这个序列位于中间的字符串。
数据保证序列长度是奇数。
例：k=2,s="az",t="bf"
序列就会是：[az,ba,bb,bc,bd,be,bf]
中间的字符串是：bc


$Solution$

这道题实际上就是让求一下26进制加法以及求中间数
遇见这种不熟悉的我们最好模拟一下我们熟悉的类似运算，比如10进制运算。

那么让我们模拟一下10进制的加法及求中间数

如193，286
192 + 286 = 478
百位4/2=2 十位 7/2=3 个位10+8/2=9
所以说如果当前位为奇数，那么除以2以后，下一位需要加上10

那么类比到26进制里，也是一样

$Code$


```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>

#define over(i,s,t) for(register int i = s;i <= t;++i)
#define lver(i,t,s) for(register int i = t;i >= s;--i)
//#define int __int128
#define lowbit(p) p&(-p)
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;

const int N = 2e5+7;

int n,m,k;
string s1,s2;
int arr[N];
int up,a;
int main()
{
    scanf("%d",&k);
    cin>>s1>>s2;
    lver(i,k-1,0){
        int a = s1[i] - 'a';
        int b = s2[i] - 'a';
        arr[i] = a+b+up;
        if(arr[i]>=26 && i != 0)up = 1,arr[i] -= 26;//26进制，注意进位
        else up = 0;
    }
    over(i,0,k-1){
        if(arr[i]&1)
            arr[i+1] += 26;
        arr[i] /= 2;
    }
    over(i,0,k-1){
        printf("%c",arr[i] + 'a');//还原为字母
    }
    puts("");
    return 0;
}

```


---

