# 困难的串 Krypton Factor

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=65

[PDF](https://uva.onlinejudge.org/external/1/p129.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/acf4a8193efdffb3da55bab10c0c0b1353f2dc09.png)

## 样例 #1

### 输入

```
7 3
30 3
0 0```

### 输出

```
ABAC ABA
7
ABAC ABCA CBAB CABA CABC ACBA CABA
28```

# 题解

## 作者：苍穹狮鹫 (赞：7)

### 这是蒟蒻的题解
第一步是循环读入

第二步是调用run（也就是搜索函数）

在每一次加入一个字母时都要判断（调用check函数），如果解足够就输出

#### PS 输出要注意

------------

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,l;
char s[10001];//搜索时填写
int ok=0;//如果ok==1说明当前有解
int cnt;//计数
bool check(int i)//此函数判断填的串是不是一个困难的串
{
	int qq=0;
	for(int k=1;k<=i/2;k++)
	{
		qq=0;
		for(int j=0;j<k;j++)
		if(s[i-j]==s[i-k-j])
		qq++;
		else
		break;
		if(qq==k)
		return false;
	}
	cnt++;
	if(cnt==n)
	{
		ok=1;
		for(int j=0;j<i;j++)
		{
		
		if(j%64==0&&j!=0)//每17个组就换一次行
		printf("\n");
		else if(j%4==0&&j!=0)//每一个组打一次空格
		putchar(' ');
		printf("%c",s[j+1]);
		}
		
		printf("\n");
		printf("%d\n",i);
	}
	return true ;
}
void run(int i)//搜索
{
	//if(i==7)
	//printf("yes");
	for(int j=0;j<l;j++)
	if(s[i-1]!='A'+j&&cnt<n)//末尾的字母一定不会等于现在添加的
	{
		s[i]=j+'A';
		if(check(i))
		run(i+1);
	}
	return ;
}
int main()
{
	while(1)//循环读入
	{
		cnt=0;
		//memset()
		ok=0;
		scanf("%d %d",&n,&l);
		if(n==0&&l==0)
		break; 
		run(1);
		if(ok==0)
		printf("No answer.\n");
	}
	return 0;
}
```
终于结束了

祝大家AC++


------------


---

## 作者：tzl_Dedicatus545 (赞：5)

**1.题意分析**

这道题很容易看出，是一道 `dfs` 的题目，再根据题目中要求字典序最小的提示，我们可以发现应该优先加字符，让后再考虑回溯。

**2.一些坑点**

- 应该是 $16$ 组一换行，题目没写出来。

**3.详细讲解**

我们先 `dfs` 一遍，因为要求字典序最小，所以我们先加字符，再回溯，如下所示：

$$\texttt{A}\to\texttt{AA(failed)}\to\texttt{AB(OK)}\to\texttt{ABA(OK)}\to \texttt{ABAA(failed)}\to \texttt{ABAB(failed)} \to \texttt{ABAC(OK)}$$

到此，思路已经很明显了，我们定义一个 `cnt` ，每次 `dfs` 时都加 $1$ ，等 `cnt` 为 $n+1$ 时即可。

**AC Code:**

```cpp
//By: Luogu@?炭治郎?(308854)
#include <bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f;

int n,l;

void Print(string s)
{
	int t=s.size();

	int nowoutput=0;

	if(s.size()%4==1)
		s+="   ";
	else if(s.size()%4==2)
		s+="  ";
	else if(s.size()%4==3)
		s+=" ";

	s=' '+s;

	for(int i=1;i<s.size();i+=4)
	{
		if(s[i]!=' ')
			cout<<s[i];
		if(s[i+1]!=' ')
			cout<<s[i+1];
		if(s[i+2]!=' ')
			cout<<s[i+2];
		if(s[i+3]!=' ')
			cout<<s[i+3];

		nowoutput++;

		if(nowoutput==16)
		{
			nowoutput=0;

			cout<<endl;

			continue ;
		}
		if(i+4<s.size() && i+3<=s.size())
			cout<<' ';
	}

	if(nowoutput==0)
		cout<<t;
	else
		cout<<endl<<t;
}

int num=0;

bool dfs(int step,string nowstr)
{
	num++;

	if(num==n+1)
	{
		num++;

		Print(nowstr);

		return true;
	}

	for(int i=1;i<=l;i++)
	{
		char nowadd=i-1+'A';

		nowstr+=nowadd;

		//cout<<i<<" "<<step<<' '<<nowadd<<' '<<nowstr<<endl;

		string str=" "+nowstr;

		bool Flag=true;

		for(int j=1;j<=step;j++)
		{
			if(step-2*j+2<1)
				break ;

			string str1,str2;

			for(int k=step-2*j+2;k<=step+1-j;k++)
				str1+=str[k];

			for(int k=step-j+2;k<=step+1;k++)
				str2+=str[k];

			if(str1==str2)
			{
				Flag=false;

				break;
			}
		}

		if(!Flag)
		{
			string ttt;

			//cout<<nowstr<<endl;

			for(int j=0;j<nowstr.size()-1;j++)
				ttt+=nowstr[j];

			nowstr=ttt;

			continue;
		}

		if(dfs(step+1,nowstr))
			return 1;

		string ttt;

		for(int j=0;j<nowstr.size()-1;j++)
			ttt+=nowstr[j];

		nowstr=ttt;

		continue;
	}

	return false;
}

signed main()
{
	while(1)
	{

		cin>>n>>l;

		num=0;

		if(n==0)
			break;

		dfs(0,"");
		cout<<endl;
	}

	return 0;
}

```


---

## 作者：wangsiyuanZP (赞：3)

## 思路分析
输入两个数 $K$ , $L$ ，分别代表由前 $L$ 个字符组成的，字典序第 $K$ 小的困难的串。  
定义一个计数器 $cnt$ 记录目前有几个符合要求的  
本题使用 `DFS` 算法，传入一个字符串 $S$  
如果 `cnt == N` 输出 $S$   
如果 `cnt > N` 结束 `return;`  
如果 `cnt < N`    
枚举 $S$ 的下一位： $A_1,A_2,\cdots,A_L$($A_i$代表第 $i$ 个字母) 并得到新字符串 $S_2$  
检查 $S_2$ ：设 $S_2$ 的长度为 $len$ ,枚举 $S_2$ 的最后两段，长为 $1,2,\cdots,len \div2$位，如果对于任意长度两段都不相同，就调用 `DFS` 传入 $S_2$ 继续递归，并将 `cnt++`   
`DFS`过程：  
`A(OK)→AA(FAIL,A=A)→AB(OK)→ABA(OK)→`  
`ABAA(FAIL,A = A)→ABAB(FAIL,AB = AB)→ABAC(OK)`  
证明得到的 $S_2$ 符合要求，举例`ABAC`：  
![](https://cdn.luogu.com.cn/upload/image_hosting/k7r80bcp.png)
可以看到 $len=$ $\color{brown}{2}$ 、 $\color{red}{3}$ 、 $\color{orange}{4}$ 时检查了所有的题目要求($A \neq B$ , $B \neq A$ , $A \neq C$ , $AB \neq AC$)  
## 
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 85;//长度不超过80
char c[N];//记录目前的答案
int n,l,cnt;

void dfs(int len){
	if (cnt>n) return;//找到答案后退出，避免TLE
	if (cnt == n){
		for (int i = 0;i<len;i++){
			if (i%4 == 0 && i){//4字符空格 64字符换行 i = 0时不换行
				if (i%64 == 0) printf("\n");
				else printf(" ");
			}
			printf("%c",c[i]);			
		}
		printf("\n%d\n",len);
		return;
	}
	for (int i = 0;i<l;i++){
		c[len] = 'A'+i;
		bool flag;
		for (int j = 1;j<=(len+1)/2;j++){//c[len-j+1~len] 是否等于 c[len-2j+1~len-j]
			flag = true;
			for (int k = len-2*j+1;k<=len-j;k++){
				if (c[k]!=c[k+j]){
					flag = false;
					break;
				}
			}
			if (flag) break;
		}
		if (!flag || (len<1 || len == 1 && c[0]!=c[1])){
			cnt++;
			dfs(len+1);
		}
	}
}

int main(){
	do{//全局变量默认n = 0,l = 0 while不会执行
		scanf("%d%d",&n,&l);
		memset(c,0,sizeof(c));
		cnt = 0;
		if (n!=0 && l!=0){
                    dfs(0);
                }
	} while(n!=0 && l!=0);
	return 0;
}
```

---

## 作者：yinhy09 (赞：3)

## 思路分析：
这道题是一道`DFS`函数递归题。

UVA题一个特殊的难点就是循环输入输出，这道题也一样。不过重点是检测函数（`checkstring`），也就是验证一个串是不是困难的串的函数。

## 代码讲解：

### 1.`checkstring`检测函数：

用全局变量数组`ans`用来储存答案，在过程中为了方便运算，最好先用`int`整形保存ASCII码即可。上个图片讲述一下思路：
![](https://cdn.luogu.com.cn/upload/image_hosting/conct3xz.png)


看起来思路简单，但是写起来容易错。


### 2.`DFS`递归函数

定义全局变量`num`保存现在枚举到了第几个串，所以只要`num=n`时，`DFS`递归就输出并且跳出。

### 3.输出函数
注意：$4$ 个字符一空格，$64$ 个字符一换行！
因为UVA不省略换行和空格，所以注意格式，否则欲哭无泪~~


### 4.循环读入
用`while`循环读入，如果是 $0$ 就退出

注意每算完一个都要清空全局变量，否则就不知道算出来的是什么了~

## 最后，附上AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l;
int len=0;
int ans[1005];
int num=0;
void empty()
{
	len=0;
	for(int i=1;i<=105;i++) ans[i]=0;
	num=0;
} 
bool checkstring(int a)
{ 
	int flag=0;
	len++;
	ans[len]=a;
	for(int i=1;i<=len/2;i++)
	{
		flag=0;
		for(int j=1;j<=i;j++)
		{
			if(ans[len-j+1]!=ans[len-i-j+1])
			{
				break;
			}
			else
			{
				flag++;
			}
		}
		if(flag==i) 
		{
			ans[len]=0;
			len--;
			return false;
		}
	}
	return true;
}
void output()
{
	for(int i=1;i<=len;i++)
	{
		printf("%c",ans[i]); 
		if(i%4==0&&i%64!=0&&i!=len) cout<<" ";
		if(i%64==0&&i!=len) cout<<endl;
	}
	printf("\n");
	printf("%d\n",len);
}
void dfs(int cur)
{
	if(num==n)
	{
		output();
		return;
	}
	else if (num<n)
	{
		for(int i=0;i<l;i++)
		{
			if(checkstring('A'+i)==true)
			{
				num++;
				dfs(cur+1);
			}
			else continue;
			ans[cur]=0;
			len--;
		}
		
	}
}
int main(){
	while(1)
	{
		scanf("%d%d",&n,&l);
		if(n==0&&l==0) break;
		dfs(1);
		empty();
	}
	return 0;
}
```


---

## 作者：Konnyaku_LXZ (赞：3)

这题直接暴力搜索就能过。

对于当前搜索到的位置，枚举该位置填的字符，判断填上该字符后的新串是否为困难的串，是则继续搜索下一位。

判断一个串是否为困难的串，我们只需要枚举这个串长度为偶数的子串，把这个子串分成左右两个部分，然后一个一个字符匹配即可。

另外，这题特别要注意的地方是输出格式：（我被坑了好久）

4个字符一个空格，16组一行。

Code：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAXN=1e5+50;

int N,K,Ans=0,Num=0;
char s[MAXN];

bool check(int len,char c){//判断串s在末尾加上字符c之后是否为困难的串 
	for(int i=2;i<=len;i+=2){//枚举偶数长度的子串 
		int l=len-i+1,mid=(l+len)>>1,cnt=0;//分成左右两部分 
		for(int j=l;j<mid;++j) if(s[j]==s[j+i/2]) ++cnt;//一一匹配 
		if(s[mid]==c) ++cnt;//对于最后一位特殊处理 
		if(cnt==i/2) return false;
	}
	return true;
}

void dfs(int t){//t表示当前搜索到的位置 
	if(Num==N) return;//搜到第N个串则返回 
	for(int i=1;i<=K;++i){
		if(Num==N) return;//搜到第N个串则返回 
		if(check(t,'A'+i-1)){//判断加上该字符后的串是否为困难的串 
			++Num;//累加个数 
			s[t]='A'+i-1;//记录答案 
			if(Num!=N) dfs(t+1);//如果还没搜到则继续深搜 
			else Ans=t;//否则保存答案 
		}
	}
}

void Init(){
	Num=0;
	scanf("%d%d",&N,&K);
}

void Solve(){
	dfs(1);//从第一位开始搜 
}

void Print(){
	for(int i=1;i<=Ans;++i){
		printf("%c",s[i]);
		if(i%64==0&&i!=Ans) printf("\n");//注意换行和空格的先后顺序 
		else if(i%4==0&&i!=Ans) printf(" ");//还要注意判断i是否等于Ans 
	}
	printf("\n%d\n",Ans);
}

int main()
{
	while(1){
		Init();
		if(N==0&&K==0) break;
		Solve();
		Print();	
	}
	return 0;
}
```

---

## 作者：多米 (赞：3)

```
#include<iostream>
using namespace std;
int n,l,cnt;
int s[100];
int dfs(int cur)// 返回 0 表示已经得到解，无法继续搜索 
{
	if(cnt++==n)// 先比较，后 ++ ，++ 后表示现在需要找的是第几个 
	{
		for(int i=0;i<cur;i++)
		{
			if(i%64==0&&i)cout<<endl;
			else if(i%4==0&&i)cout<<' ';
			cout<<char('A'+s[i]); 
		}
		cout<<endl<<cur<<endl;// 输出方案 
		return 0;
	}
	for(int i=0;i<l;i++)
	{
		s[cur]=i;
		bool ok=true;
		for(int j=1;j*2<=cur+1;j++)// 尝试长度为 j*2 的后缀 
		{
			bool equal=true;
			for(int k=0;k<j;k++)// 检查后一半是否等于前一半 
				if(s[cur-k]!=s[cur-k-j])
				{
					equal=false;
					break;
				}
			if(equal)// 后一半等于前一半，方案不合法 
			{
				ok=false;
				break;
			}
		}
		if(ok)if(!dfs(cur+1))return 0;//递归搜索，如果已经找到解，则直接退出 
	}
	return 1;
}
int main()
{
	while(cin>>n>>l&&n)
	{
		cnt=0;
		dfs(0);
	}
	return 0;
}
```

---

## 作者：DreamAndDead (赞：2)

和大家一样是深度搜索的思路，在如何判断是否有重复的方法值得一提。

标准库方法 `equal` 接受 3 个参数，

`std::equal(iter first1, iter last1, iter first2)`

可以判断两个 range `[first1, last1)` 和 `[first2, first2 + (last1 - first1))` 是否相同

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int n, L, ith;
vector<int> s;

void print_str(void) {
  for (size_t i = 0; i < s.size(); i++) {
    if (i == 0)
      ;
    else if (i % 64 == 0)
      cout << endl;
    else if (i % 4 == 0)
      cout << ' ';
    
    char c = s[i] + 'A';
    printf("%c", c);
  }

  cout << endl;

  cout << s.size() << endl;
}

void iter_hard_str() {
  if (ith == n) {
    print_str();
    return;
  }

  for (int i = 0; i < L; i++) {
    if (ith == n)
      break;
    
    s.push_back(i);

    int len = s.size();
    bool can = true;
    
    for (int l = 1; l <= len / 2; l++) {
      bool dup = equal(s.rbegin(), s.rbegin() + l, s.rbegin() + l);
      
      if (dup) {
	can = false;
	break;
      }
    }

    if (can) {
      ith++;
      iter_hard_str();
    }
    
    s.pop_back();
  }
}

int main(void) {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif

  while (true) {
    cin >> n >> L;

    if (n == 0 && L == 0)
      break;

    ith = 0;
    iter_hard_str();
  }
    
  return 0;
}

```


---

## 作者：_•́へ•́╬_ (赞：2)

## ~~似乎没有题解，我来搞一篇~~
```cpp
#include<bits/stdc++.h>//懒人专用头文件
using namespace std;
int n,l;string ans;
bool can()//判断是否为困难串
{
	if(ans.size()==1)return 1;//就一个字符
	string s="";
	for(int i=ans.size()-1;i>=ans.size()/2;--i)//从后向前
	{
		s=ans[i]+s;//加上这一个
		int j,k;
		for(j=i-1,k=s.size()-1;k>=0;--j,--k)if(ans[j]!=s[k])break;//有不一样的
		if(k<0)return 0;//都一样
	}
	return 1;//都不一样，是困难串
}

void find()
{
	for(char c='A';c<'A'+l;c++)
	{
		if(c>'A')ans.erase(ans.size()-1,1);//前面找过，要删掉
		ans+=c;
		if(can())//找到啦！(@^v^@)
		{
			n--;
			if(!n)return;//这就是我们的正解——第n个！
			find();//不是第n个，继续找
		}
		if(!n)return;
	}
	ans.erase(ans.size()-1,1);//重要！！！（我原来漏了，调了半天）返回上一层时去掉这一层的结果
}

main()
{
    for(;scanf("%d%d",&n,&l),n||l;ans="")//输入
    {
    	find();
    	for(int i=0;i<ans.size();i++)//输出
    	{
    		if(i%64==0&&i>0)putchar('\n');//需要回车
    		else if(i%4==0&&i>0)putchar(' ');//需要空格
    		putchar(ans[i]);//把这个打出来
		}
		printf("\n%d\n",ans.size());//还要长度
	}
}/**/
```
**如果前面的是困难串，那么加上一个后，只需判断最后一个与其他的构成的串是否有重复，判断时间：$O(ans.size())$**

---

## 作者：Fengxiang008 (赞：0)

### 题意：
输入正整数 $n$ 和 $L$，输出由前 $L$ 个字符组成的、字典顺序第 $n$ 小的不含相邻重复字串的字符串。 不含相邻重复字串的字符串是指：一个字符串中，任意两个相邻的字串都不相等。输出结果时，对于找到的字符串，每 $4$ 个字符间加入一个空格，每行输出 $80$ 个字符。

### 题目分析
这题乍一看好像是子集生成诶......

主要问题就在于没添加一个字符后判断是否有连续相同子串。   

由于对每个串而言，所有的前缀都是已经判断过无相同的。

所以只需要判断后缀即可。

### 代码演示：
```cpp
#include <bits/stdc++.h>
#define LL long long
#define maxn 105
#define maxm 10005
#define N 52
using namespace std;
int L, n, cnt;
char a[maxn];
 
bool check(int cur, int c) {
	char ch = 'A' + c;
	for (int i = 1; i <= (cur + 1) >> 1; ++i) {
		bool same = true;
		for (int j = 0; j < i; ++j) {
			if (a[cur - j] != a[cur - i - j]) same = false;
		}
		if (same) return false;
	}
	return true;
}
 
bool dfs(int cur) {
	if (cnt == n) {
		for (int i = 0; i < cur; ++i) {
			if (i % 64 && i % 4 == 0) putchar(' ');
			else if (i && i % 64 == 0) putchar('\n');
			putchar(a[i]);
		}
		printf("\n%d\n", cur);
		return true;
	}
	for (int i = 0; i < L; ++i) {
		bool ok = true;
		a[cur] = 'A' + i;
		if (check(cur, i)) {
			cnt++;
			if (dfs(cur + 1)) return true;
		}
	}
	return false;
}
 
int main() 
{
	while (~scanf("%d%d", &n, &L) && (n || L)) {
		cnt = 0;
		dfs(0);
	}
	return 0;
}
```


---

## 作者：hicode_002 (赞：0)

UVA129困难的串

https://www.luogu.com.cn/problem/UVA129

这个题目的特点是思路简单，但实现复杂

是要求一个不含相邻重复子串的字典序第k小的用ABC…的前l个字符构成的子串

由于要求具体方案且不是最优解问题，所以适用于搜索，由于是填字母的问题，所以应该用dfs

dfs要cur表示阶段，这里用cur表示当前位置要填什么字母

题目并没有明确字符串长度，而是明确了字典序，所以应该按字典序枚举，即从少到多，从小到大枚举，

每一次dfs枚举l个字母填在$b[cur]$中，然后判断是否有相邻重复子串，怎么判断呢？

一个办法是枚举所以长度为偶数的子串，判断前一半是否等于后一半，但太耗时了

对于每一次填字母来说，实际上只改变了最后一个字符，所以只需要检查最后一个字母为结尾的子串的前一半是否等于后一半即可

前一半不等于后一半说明不是相邻重复字串，否则是
因为如果能dfs到这个cur，说明之前的子串一定不是相邻重复子串

然后如果合法就继续dfs

这样是从小到大，从少到多的，所以按字典序

只需一个全局变量p记录当前的串是第几个，因为p从1开始，所以p等于k+1时说明第k个串已枚举完毕，此时可以停止递归并做标记让所以递归函数均停止，然后输出解

然后当前cur即为长度

输出是个难题，uva对空格和换行要求很严，所以要多考虑

由于长度最大80

先输出当前字符

然后因为4个一组，i从0开始，所以（i+1)%4==0时一个空格，如果i是63时不空格，输出换行。

但如果i=63时i是cur-1就不输出换行

i是cur-1且该输出空格时不输出空格

然后一个回车输出长度再一个回车，最后一行多余换行符可以。

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int k,l;char a[27],b[100],st=1,p=1;
inline void dfs(int cur){
	if(p==k+1){	
		st=0;//标记，为0代表找到合适解，停止搜索
//		int ls=1;
		for(int i=0;i<cur;++i){
			
			cout<<b[i];
//			if((i+1)%4==0&&i!=cur-1&&(i+1)/4<16)cout<<" ";
//			if((i+1)%4==0&&(i+1)/4==16&&i!=cur-1)cout<<endl;
			if(i==63&&cur!=64){//i不是cur-1时且i是63时换行
				cout<<endl;
			}else if(i<63){
				if(i!=cur-1&&(i+1)%4==0)cout<<" ";//不是cur-1且满足需求时，输出空格
			}else{
				if(i!=cur-1&&(i+1)%4==0)cout<<" ";
			}
		}
		cout<<endl;
		cout<<cur<<endl;
		return;
	}
	if(!st)return;
	++p;
	for(int i=1;i<=l;++i){
		if(!st)return;
//		cout<<22;
		b[cur]=a[i];
		int fl=1;//标记
		for(int j=cur-1;j>=0;j-=2){枚举长度为偶数以cur结尾的子串的开头
			int ok=1;
			for(int k=j+(cur-j+1)/2,ss=j;k<=cur&&ss<=cur;++k,++ss){//ss表示前一半的每个字符，k是j加上子串长度的一半
//				cout<<j+k<<" "<<k<<" k ";
				if(b[ss]!=b[k]){//只要一个字符不等就不是相邻重复子串
					
					ok=0;
					break;
				}
			}
			if(ok){//只要有一个是相邻重复子串就不合法
				fl=0;
				break;
			}
		}
		if(fl)dfs(cur+1);
	}
	
}
int main(){
	for(int i='A',j=1;i<='Z';++i,++j){
		a[j]=i;
	}
	while(scanf("%d%d",&k,&l)==2&&l&&k){
		memset(b,0,sizeof b);//多组要清空！
		st=p=1;
		dfs(0);
	}
	return 0;
}

```


---

