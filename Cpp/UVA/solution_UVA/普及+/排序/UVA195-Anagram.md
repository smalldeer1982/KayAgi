# Anagram

## 样例 #1

### 输入

```
3
aAb
abc
acba```

### 输出

```
Aab
Aba
aAb
abA
bAa
baA
abc
acb
bac
bca
cab
cba
aabc
aacb
abac
abca
acab
acba
baac
baca
bcaa
caab
caba
cbaa```

# 题解

## 作者：Acerkaio (赞：5)

[题目传送门](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=131)

### 思路 : dfs 全排列

全排列也可以用 STL 的 sort 和 next_permutation  。 

思路 : ~~人人皆会的~~ dfs 全排列 。

不会的看向 [这](https://blog.csdn.net/qq_34123044/article/details/111411457#:~:text=dfs%20%E8%A7%A3%E5%86%B3%20%E5%85%A8%E6%8E%92%E5%88%97%20%E9%97%AE%E9%A2%98%20%E8%A7%A3%E5%86%B3%E6%80%9D%E8%B7%AF%EF%BC%9A%20%E6%AF%8F%E4%B8%AA%E6%95%B0%E5%AD%97%E5%A6%82%E6%9E%9C%E8%AE%BF%E9%97%AE%E4%BA%86%EF%BC%8C%E5%B0%B1%E6%A0%87%E8%AE%B0%E4%B8%80%E4%B8%8B%EF%BC%8C%E4%B9%8B%E5%90%8E%EF%BC%8C%E5%AF%B9%E5%89%A9%E4%BD%99%E6%B2%A1%E6%9C%89%E8%AE%BF%E9%97%AE%E7%9A%84%E6%95%B0%E5%AD%97%E5%86%8D%E6%AC%A1%E8%BF%9B%E8%A1%8C%E8%AE%BF%E9%97%AE%EF%BC%8C%E4%B9%8B%E5%90%8E%EF%BC%8C%E5%86%8D%E5%AF%B9%E8%AF%A5%E6%95%B0%E5%AD%97%E5%8F%96%E6%B6%88%E6%A0%87%E8%AE%B0%EF%BC%8C%E4%BB%A5%E4%BE%BF%E8%AE%A9%E6%95%B0%E5%AD%97%E5%BE%97%E5%88%B0%E8%AE%BF%E9%97%AE%20%E6%95%B0%E5%AD%97%E7%9A%84%20%E5%85%A8%E6%8E%92%E5%88%97,%E4%BB%8A%E5%A4%A9%E5%A4%8D%E7%9B%98%E4%B8%80%E4%B8%8B%E8%BE%93%E5%87%BA%20%E5%85%A8%E6%8E%92%E5%88%97%20%E7%9A%84%E7%AE%97%E6%B3%95%2C%E9%9D%9E%E5%B8%B8%E6%84%9F%E8%B0%A2%E3%80%8A%E5%95%8A%E5%93%88%E7%AE%97%E6%B3%95%E3%80%8B%E7%9A%84%E4%BD%9C%E8%80%85%E5%95%8A%E5%93%88%E7%A3%8AO%20%28%E2%88%A9_%E2%88%A9%29O%2C%E7%94%A8%E8%BF%99%E4%B9%88%E7%AE%80%E5%8D%95%E7%9A%84%E4%B8%80%E4%B8%AA%E5%B0%8F%E5%BA%94%E7%94%A8%E8%AF%B4%E6%98%8E%E4%BA%86%20%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2%20%E7%9A%84...%20dfs%20%28step%2B1%29%3B%2F%2F%E7%BB%A7%E7%BB%AD%E4%B8%8B%E4%B8%80%E6%AD%A5%E3%80%82.) 。

注意题解区 dalaos 所说 : 样例输入后有重复问题 ， 这里我和那位 dalao 一样采用在递归前计数 ， 递归后加回去 。

```cpp
/*错误代码*/
void abe(int e) {
	if (len + 1 == e) {  
		pr();
		return ;
	}
	for (int i = 'A'; i <= 'Z'; i++) {  
		if (js[i]) {  
			an[e] = i;
			abe(e + 1);  
		}
		if (js[i - 'A' + 'a']) {  
			an[e] = i - 'A' + 'a';
			abe(e + 1);  
		}
	}
}
```

核心代码

```cpp
void abe(int e) {
	if (len + 1 == e) {  //确定边界 
		pr();
		return ;
	}
	for (int i = 'A'; i <= 'Z'; i++) {  //枚举字母 
		if (js[i]) {  //要出现的小写字母 
			js[i] = js[i] - 1;
			an[e] = i;
			abe(e + 1);  //递归dfs
			js[i] += 1;
		}
		if (js[i - 'A' + 'a']) {  //要出现的小写字母 
			js[i - 'A' + 'a'] = js[i - 'A' + 'a'] - 1;
			an[e] = i - 'A' + 'a';
			abe(e + 1);  //递归dfs
			js[i - 'A' + 'a'] += 1;
		}
	}
}
```

附上有注释完整 code : 
```cpp
#include <bits/stdc++.h>
using namespace std;
int len, js[9999999];
char an[9999999];

void pr()  //输出 
{
	for (int i = 1; i <= len; i++) {
			printf("%c", an[i]);
		}
		printf("\n");
}

void abe(int e) {
	if (len + 1 == e) {  //确定边界 
		pr();
		return ;
	}
	for (int i = 'A'; i <= 'Z'; i++) {  //枚举字母 
		if (js[i]) {  //要出现的小写字母 
			js[i] = js[i] - 1;
			an[e] = i;
			abe(e + 1);  //递归dfs
			js[i] += 1;
		}
		if (js[i - 'A' + 'a']) {  //要出现的小写字母 
			js[i - 'A' + 'a'] = js[i - 'A' + 'a'] - 1;
			an[e] = i - 'A' + 'a';
			abe(e + 1);  //递归dfs
			js[i - 'A' + 'a'] += 1;
		}
	}
}


int main() {
	int n;
	cin >> n;
	string a;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		len = a.size();
		memset(js, 0, sizeof(js));
		for (int i = 0; i < len; i++) {
			js[a[i]]++;  //计入 
		}
		abe(1);
	}
	return 0;
}
```



---

## 作者：Water_Cows (赞：3)

我又来写题解了，~~首先说明一下，这题评蓝真的有点高啊~~。

这就是深搜的裸题，我看大家都是用$c++$强大的$STL$的`sort`和`next_permutation`写的，可是我太蒟了，不会啊/kk，所以我来水一篇手写`dfs`的题解。

***
首先，我们打出全排列的程序。

然后，你会发现样例都过不了，问题在哪里？

我们模拟一下：

比如aab这个数据

- 第一次$a_1=a,a_2=a ,a_3=b$
- 第二次$a_1=a,a_2=b ,a_3=a$
- 第三次$a_1=a,a_2=a ,a_3=b$
- ……

你发现了什么？第一次和第三次是一样的！！

那怎么办呢？

**我们记录每个字母出现的次数**~~（虽然这就是个P话）~~

因为有重复元素，所以每次只让没有重复的去全排列。

看看代码吧：

```cpp
for(int i='A'; i<='Z'; i++) 
    {
        if(b[i])  // 这里就完美的做到了只选出现过了字符，所以就不会有重复的了
        {
            b[i]=b[i]-1;  
            a[x]=i;
            dfs(x+1);
            b[i]=b[i]+1;  // 回溯就不用我说了吧
        } 
        if(b[i-'A'+'a']) // i-'A'+'a'是把大写转成小写的ASCII码
        {
            b[i-'A'+'a']=b[i-'A'+'a']-1;
            a[x]=i-'A'+'a';
            dfs(x+1);
            b[i-'A'+'a']=b[i-'A'+'a']+1;
        } // 因为要A<a<B<b......<Z<z,所以我只能这么写 ~ QAQ
    }
```

于是，我们就做到了没有重复的

(~~其他就不用我说了吧，不会就别做这题了~~)

***

下面送上完整$Code$：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int n, ans, b[10001], c[10001];
char a[10001];
string s;

inline void dfs(int x)
{
    if(n+1==x) // 如果到头了
    {
        for(int i=1; i<=n; i++) printf("%c", a[i]); // 输出
        // 同样,把ASCII码转成字符再输出
        puts("");
        return ; // 返回
    }
    for(int i='A'; i<='Z'; i++) 
    {
        if(b[i])  // 这里就完美的做到了只选出现过了字符，所以就不会有重复的了
        {
            b[i]=b[i]-1;  
            a[x]=i; // 记录答案
            dfs(x+1);
            b[i]=b[i]+1;  // 回溯就不用我说了吧
        } 
        if(b[i-'A'+'a']) // i-'A'+'a'是把大写转成小写的ASCII码
        {
            b[i-'A'+'a']=b[i-'A'+'a']-1;
            a[x]=i-'A'+'a';
            dfs(x+1);
            b[i-'A'+'a']=b[i-'A'+'a']+1;
        } // 因为要A<a<B<b......<Z<z,所以我只能这么写 ~ QAQ
    }
}

signed main()
{
    int t;
    scanf("%d", &t);
    for(int i=1; i<=t; i++)
    {
        cin>>s;
        n=s.length();
        memset(b, 0, sizeof(b)); // 记得清空
        for(int i=0; i<s.length(); i++) 
            b[s[i]]++; // 统计每个字母出现了几遍
        // 有人会说s[i]是一个字符啊,为什么能做下标啊？
        // 回答：c++是很强大的，在作下标的时候自动转成ASCII码了
        dfs(1);
    } 
    return 0; // 完结撒花
}
```

~~最后：求管理员大大通过~~

---

## 作者：Scorilon (赞：1)

$To$ [题目](https://www.luogu.com.cn/problem/UVA195)

主要思路：全排列 + 亿点点小技巧。

不会全排列的可以先把这道题过了 [P1706](https://www.luogu.com.cn/problem/P1706)。

这道题的难点就在于有重复的单词，只记一次。

第一个想法是将所有以生成的单词记录下来，然后每次判断是否为已存在，但是很明显，你不是 TLE 就是 MLE ~~有哪位勇士去试一下吗~~。

所以，要换一种做法，**记录原单词每个字母出现的次数**。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n;//共输入n组数据
char s[9999999];//单词
int len;//长度
int used[9999999];//每个字母出现次数
char a[9999999];//原单词
void dfs(int x){
	if(x>len){//如果长度已足
		for(int i=1;i<=len;i++){
			printf("%c",s[i]);//输出
		}
		printf("\n");//换行
		return;//结束函数
	}
	for(int i='A';i<='Z';i++){//枚举字母，不用小写是因为在ASCII码中小写大于大写
		if(used[i]){//如果大写字母可以用
			used[i]--;//减少一次使用次数
			s[x]=i;//此位为i
			dfs(x+1);//确定下一位
			used[i]++;//回溯释放状态
		}
		if(used[i-'A'+'a']){//如果小写字母可以用
			used[i-'A'+'a']--;//减少一次使用次数
			s[x]=i-'A'+'a';//此位为i的小写
			dfs(x+1);//确定下一位
			used[i-'A'+'a']++;//回溯释放状态
		}
	}
}
int main(){
	scanf("%d",&n);//输入n
	while(n--){
		memset(used,0,sizeof(used));//记得初始化
		cin>>a;//输入这个单词
		len=strlen(a);//单词长度
		for(int i=0;i<=len;i++){
			used[a[i]]++;//记录每个字母的可使用次数
		}
		dfs(1);//开始全排列
	}
	return 0;//完结撒花
}
```


---

## 作者：HsKr (赞：1)

思路：此题为全排列问题，只需要将字符串从第一个排列遍历到最后一个排列，输出即可。

题目中的顺序（省略掉单引号）：

`A<a<B<b<C<c<D<d<...<Y<y<Z<z`

用STL的`sort`和`next_permutation`可以做的很优雅，只是cmp要自己定义一下。

`next_permutation`在最后一个排列中返回的是0。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
char s[1000];
bool cmp(char a,char b){//sort和next_permutation的比较函数
	char la=tolower(a),lb=tolower(b);//全部转换成小写
	if(la==lb) return a<b;//字母一样比较它们的大小写
	else return la<lb;//字母不一样就比较它们的字母
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){//多组数据
		scanf("%s",s);//输入
		int l=strlen(s);//取长度
		sort(s,s+l,cmp);//第一个排列
		do{
			printf("%s\n",s);//输出当前排列
		}while(next_permutation(s,s+l,cmp));//（不是最后一个排列就继续）下一个排列
	}
	return 0;
}
```


---

## 作者：_Anchor (赞：1)

# 枚举

## 这题可以dfs暴力也可以STL

分析：照着题意暴力枚举排列即可，注意字典序

### 搜索

直接暴力枚举就是了，记得回溯和最后边界情况的判断，

此处就不多说了，其实这题就是枚举全排列的一个模板，

只不过是多了一个字典序，可以给刚学dfs的人练练手

### STL

函数：next_permutation(起始地址,终止地址,排序函数)

作用：把一个区间内的数修改成这一串数的下一个排列

注意这里我们要的是字典序，所以我们可以先排序一遍

排序：sort就行了，应该都知道吧。。。

然后就可以直接不断地生成排列再输出即可

注意：next_permutation内的排列若已经是最后一个，则返回
false

如果不是，会执行操作并返回true

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
inline int inc(int x,int v,int mod){x+=v;return x>=mod?x-mod:x;}
inline int dec(int x,int v,int mod){x-=v;return x<0?x+mod:x;}
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if(x==0){putchar(48);return;}int len=0,dg[20];while(x>0){dg[++len]=x%10;x/=10;}for(register int i=len;i>=1;i--)putchar(dg[i]+48);}
bool cmp(char a,char b){
    if(a-b==32) return false;
    if(b-a==32) return true;
    if(a>='a'&&b<='Z') return a-32<b;
    else if(a<='Z'&&b>='a')return a+32<b;
    else return a<b;
}
int m,n;
string s;
int main(){ 
    m=read();
    while(m--){
        cin>>s;
        n=s.length();
        sort(s.begin(),s.end(),cmp);
        cout<<s<<endl;
        while(next_permutation(s.begin(),s.end(),cmp)) cout<<s<<endl;
    }
    return 0;
}


```


---

## 作者：LegendaryGrandmaster (赞：0)

全排列写法。

先将字符串进行排序，之后 `next_permutation` 全排列即可。

但是排序时的规则如下：

1. 相同字母大小写不同大写字母排在前。
2. 大小写相同 `ASCII` 码小的字母排在前。

所以排序时两个字符差的绝对值为 $32$，即相同字母大小写不同，则把大写放前；

否则把两字符大小写统一，`ASCII` 码小的放前。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(char c1,char c2)
{
	if(abs(c1-c2)==32)return c1<c2;
	else return toupper(c1)<toupper(c2);
}
int main()
{
    int t;
    cin>>t;
    while(t--){
    	string st;
    	cin>>st;
    	int n=st.size();
    	sort(st.begin(),st.end(),cmp);
    	do{
    		cout<<st<<'\n';
    	}while(next_permutation(st.begin(),st.end(),cmp));
    }
}
```

---

## 作者：myyyIisq2R (赞：0)

[UVA195 Anagram](https://www.luogu.com.cn/problem/UVA195)


## STL做法
直接使用公式 `next_permutation`，注意 `next_permutation` 可以传入判断函数，坑点在于判断字母优先级顺序。
## 坑点
题中字母的优先级：

$ \texttt{A} < \texttt{a}<\texttt{B}<\texttt{b}<\texttt{C}<\texttt{c}<\texttt{D}<\texttt{d}<\cdots<\texttt{Y}<\texttt{y}<\texttt{Z}<\texttt{z}$

比较函数清晰易懂。
## 参考程序
```cpp
#include <bits/stdc++.h>
using namespace std;

bool timcompare( char a, char b )
{
	if ( islower(a) != 0 && islower(b) != 0 )   // A and B
	{
		return a < b;
	}
	else if ( islower(a) == 0 && islower(b) == 0 )  // a and b
	{
		return a < b;
	}
	else if ( islower(a) != 0 && islower(b) == 0 )  // a and B
	{
		if ( toupper(a) == b )
			return false;
		else
			return toupper(a) < b;

	}
	else if ( islower(a) == 0 && islower(b) != 0 )  // A and b
	{
		if ( a == toupper(b) )
			return true;
		else
			return a < toupper(b);
	}
	else
		return a < b;
}

int main()
{

	int testcases;
	int a;
	cin >> testcases;
	for ( a = 0; a < testcases; a++ )
	{
		string input;
		cin >> input;
		sort( input.begin(), input.end(), timcompare );
		do
		{
			cout << input << '\n';
		}
		while ( next_permutation( input.begin(), input.end(), timcompare ));
	}
	return 0;
}

```
```cpp
#include <bits/stdc++.h> 
using namespace std;
bool cmp(char a, char b)
{
	return tolower(a) == tolower(b) ? a<b :tolower(a)<tolower(b); 
   //可以参考上面的优先级理解
}
int main()
{
    char s[110];
    int t = 0;
    cin >> t;
    while (t--)
    {
        cin >> s;
        int len = strlen(s);
        sort(s, s+len,cmp);
        do
        {
            cout << s << endl;
        }while (next_permutation(s, s+len,cmp));
    }
   return 0;
}
```

---

## 作者：李柯欣 (赞：0)

题目传送门：[UVA195](https://www.luogu.com.cn/problem/UVA195)。

[更好的阅读感受](https://www.luogu.com.cn/blog/likexin/solution-uva195)？


## 题意：
给定一个字符串，输出其去重后的全排列。

## 思路：
显然是一个裸的 DFS，直接暴力枚举即可。

首先对字符串排序：

```cpp
bool cmp(char a,char b){
    if(a>='A'&&a<='Z'){//a 为大写。
        if(b>='A'&&b<='Z') return a<b;//b 也为大写。
        else return a+32<=b;//b 为小写。
    }else{//a 为小写。
        if(b>='a'&&b<='z'){ return a<b;//b 也为小写。
        else return a-32<b;//b 为大写。
    }
}
```
再 DFS 就很简单了，直接上代码：
```cpp
#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
int n;
int cc[1000001];
map<int,char> nm;
int vis[1000001];
int s[1000001];
//排序。
bool cmp(char a,char b){
    if(a>='A'&&a<='Z'){
        if(b>='A'&&b<='Z') return a<b;
		else return a+32<=b;
    }else{
        if(b>='a'&&b<='z'){ return a<b;
		else return a-32<b;
    }
}
//裸 dfs。
void dfs(int x){
	if(x==n){//输出。
		for(int i=0;i<n;i++){
			cout<<nm[s[i]-1];
		}
		cout<<endl;
	}
	map<char,int> mn;
	for(int i=1;i<=n;i++){ 
		if(vis[i]==1){//去重 1。
			continue;
		}
		if(mn[nm[i-1]]==1){//去重 2。
			continue;
		}
		mn[nm[i-1]]++;
		s[x]=i;
		vis[i]++;
		dfs(x+1);
		vis[i]--;
	}
} 
int tt;
int main(){
	cin>>tt;
	while(tt--){
		//多组数据先清空。
    	nm.clear();
    	string aa;
        //读入。
    	cin>>aa;
    	n=aa.length();
    	for(int i=0;i<n;i++){
    		cc[i]=aa[i];
    	} 
        //排序。
    	sort(cc,cc+n,cmp);
    	for(int i=0;i<n;i++){
    		char nn;
    		nn=char(cc[i]);
    		nm[i]=nn;
    	}
    	dfs(0);//dfs。
	} 
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/83759734)。

---

## 作者：pokefunc (赞：0)

### 题意

给定一个只包含大写字母和小写字母的字符串，把其所含的字母排列组合后产生的所有单词（包括原单词）按照字典序输出，每行一个。如果有重复的单词，只记一次。大写字母和小写字母视为不同的字母。

### 思路

~~STL大法好！~~

这道题其实就是求全排列，可以用dfs，但是现在比赛毕竟是可以用 `next_permutation` 哒！

具体的，先把原字符串排序得到最小字典序排列，从第一个开始逐个 `next_premutation` 直到最后一个。

`next_premutation` 和 `sort` 一样是可以传比较函数的，这道题的比较方法是先转小写比大小再比是大（写）是小（写）。

实测20行左右就可搞定。

Code:

```cpp
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cctype>
using namespace std;
bool cmp(char a,char b){
	char x=tolower(a),y=tolower(b); //tolower是cctype库的函数，作用是转小写
	if(x==y) return a<b;
	else return x<y;
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		char s[100003];
		scanf("%s",s);
		sort(s,s+strlen(s),cmp);
		do{printf("%s\n",s);}while(next_permutation(s,s+strlen(s),cmp));
	}
	return 0;
}
```



---

## 作者：西卡洛斯 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/UVA195)

关于本题有两种做法， DFS 和 STL 函数，这里介绍 STL 做法。

题中字母的优先级：
 - 排在前的字母大于排在后的字母。 （如 $z > a$）
 - 一个字母的小写大于它的大写。（如 $a > A$）

完整的顺序就是

$ A<a<B<b<C<c<D<d<...<Y<y<Z<z $

可能与一般想到的正好相反。

本题主要使用到了 STL 库中的全排列 next_permutation() 函数。

使用方式：

```cpp
do
{
    ...   
}while(next_permutation(a,a+n));
```
 
例如我们在循环外定义 `string s='abc';`，循环里输出这个字符串，那么程序输出为：

	abc
	acb
	bac
	bca
	cab
	cba


本题中的 cmp 函数需要我们手写。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
bool cmp(char a,char b)
{
	return (tolower(a)==tolower(b))?(a<b):(tolower(a)<tolower(b));
	/*char ca=tolower(a),cb=tolower(b);//tolower()将大写转为小写
	if(ca==cb) return a<b;//字母相同，比较大小写
	else return ca<cb;*///字母不同，比较顺序
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		string str;
		cin>>str;
		sort(str.begin(),str.end(),cmp);//先得到字符串的最小排序
		do
		{
			cout<<str<<endl;
		}while(next_permutation(str.begin(),str.end(),cmp));
	}
	return 0;
}
```


---

## 作者：血色黄昏 (赞：0)

虽然此题有点意思，但评绿有点虚高？

~~做了这一题后我智頽就从五蓝变成三蓝二绿了/kk~~

一道深搜好题，可惜窝又菜又懒，不会打深搜，就用全排列函数写掉了这题，练习C++内置函数好题w

思路就是将这个字符串排序，然后手写个符合题目条件判断的cmp函数，直接上去拿排列函数即可，注释在代码里

Code qwq

```
#include<bits/stdc++.h>
using namespace std;
int T;
char s[110];//字符数组，相当于字符串
bool cmp(char a, char b)//比较两个char大小
{
	return tolower(a) == tolower(b)?a<b:tolower(a)<tolower(b);//tolower函数将大写转小写，如果相同判断哪个大写那个小写，不然直接判断哪个字母靠前
}
int main()
{
	cin>>T;
	while(T--)//T组数据
	{
		cin>>s;
		int len = strlen(s);//长度
		sort(s, s + len, cmp);//先排序找最小
		do
		{
			cout<<s<<endl;
		}while(next_permutation(s, s + len, cmp));//按照要求方式排列，要自己手写个cmp
	}
	return 0;
}
```

期末考前两天作品，rp++

---

