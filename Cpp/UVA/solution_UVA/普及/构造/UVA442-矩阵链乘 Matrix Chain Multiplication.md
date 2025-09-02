# 矩阵链乘 Matrix Chain Multiplication

## 题目描述

## 矩阵链乘


​  假设你必须评估一种表达形如 A*B*C*D*E，其中 A,B,C,D,E是矩阵。既然矩阵乘法是关联的，那么乘法的顺序是任意的。然而，链乘的元素数量必须由你选择的赋值顺序决定。

​  例如，A，B，C分别是 50 * 10 ，10 * 20 和 20 * 5 的矩阵。现在有两种方案计算 A * B * C ,即（A * B) * C 和 A*(B * C)。  
   第一个要进行15000次基本乘法，而第二个只进行3500次。

​  你的任务就是写出一个程序判定以给定的方式相乘需要多少次基本乘法计算。

## 样例 #1

### 输入

```
9
A 50 10
B 10 20
C 20 5
D 30 35
E 35 15
F 15 5
G 5 10
H 10 20
I 20 25
A
B
C
(AA)
(AB)
(AC)
(A(BC))
((AB)C)
(((((DE)F)G)H)I)
(D(E(F(G(HI)))))
((D(EF))((GH)I))```

### 输出

```
0
0
0
error
10000
error
3500
15000
40500
47500
15125```

# 题解

## 作者：ICE_Wol (赞：6)


本题为紫书P141例题6 - 3 

遇到这样简单的表达式解析的题目可以用一个栈搞定 

- 将元素入栈 并取出栈顶两个元素运算再将结果入栈

关键部位解释见代码注释

```c
include<cstdio>
include<iostream>
include<stack>
include<string>
using namespace std;
define rep(i,a,n) for(int i = a;i < n;i++) //偷懒大法好

struct M{
	int a,b; 
    M(int a = 0, int b = 0):a(a),b(b){} 
    //构造函数，将成员变量a初始化为参数a，成员变量b初始化为参数b
}m[26]; //声明一个M型数组m

stack<M> s;//声明一个M型的栈储存表达式

int main(){
	int n;
    cin >> n; 
    rep(i,0,n){ 
    	string name; 
        cin >> name; 
        int k = name[0] - 'A';//将字母与数组对应起来 
        cin >> m[i].a >> m[i].b;//输入矩阵
    } 
    string expr;
    while(cin >> expr){ 
    	int len = expr.length();
        bool error = false;
        int ans = 0; 
        rep(i,0,len){
        	if(isalpha(expr[i])) 
            s.push(m[expr[i] - 'A']);
            //当字符串第位为字母时将该矩阵对应的行列入栈 
            else if(expr[i] == ')'){
            //当字符为反括号时 
            	M m2 = s.top(); s.pop();//将栈顶元素取出 
                M m1 = s.top(); s.pop(); 
                if(m1.b != m2.a){ error = true; break;}
                //不满足链乘条件时error
                ans += m1.a m1.b m2.b;
                s.push(M(m1.a,m2.b));
                //将乘法结果入栈，这就是之前构造函数的妙用了（妙个屁
            } 
		} 
        if(error) printf("error\n"); 
        else printf("%d\n",ans);//打印答案 
    } 
	return 0;
}
```


---

## 作者：EuphoricStar (赞：3)

本题的关键是解析表达式。本题的表达式比较简单，可以用一个栈来完成：遇到字母时将矩阵入栈，遇到用右括号时将栈顶的两个矩阵出栈并计算，然后将结果入栈。**因为输入保证合法，括号无需入栈。**

代码如下（关键部分有注释）：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct matrix
{
    int a, b;
} m[128];
int n;

int main()
{
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        char name;
        cin >> name;
        cin >> m[name].a >> m[name].b;
    }
    string expr;
    while (cin >> expr)
    {
        bool error = 0;
        int ans = 0;
        stack<matrix> s;
        for (int i = 0; i < expr.size(); ++i)
        {
            // 如果当前字符是字母就将字母对应的矩阵入栈
            if (isalpha(expr[i])) s.push(m[expr[i]]);
            // 如果当前字符是右括号
            else if (expr[i] == ')')
            {
                // 将栈顶的两个矩阵出栈
                matrix m2 = s.top();
                s.pop();
                matrix m1 = s.top();
                s.pop();
                // A 的列数不等于 B 的行数，乘法无法进行
                if (m1.b != m2.a)
                {
                    error = 1;
                    break;
                }
                // 计算结果并将新矩阵入栈
                ans += m1.a * m1.b * m2.b;
                s.push({m1.a, m2.b});
            }
        }
        if (error) cout << "error\n";
        else cout << ans << '\n';
    }
    return 0;
}
```


---

## 作者：xiaomimxl (赞：1)

### 题意：
输入题目指定数量个矩阵的维度和一个矩阵链乘的表达式，输出乘法的次数，如果乘法无法进行，则输出   $error$

------------
### 思路：
 栈对表达式求值有着特殊的作用，本题表达式简单，可以用一个栈来完成，遇到字母时入栈，遇到右括号时出栈并且计算，之后算出的结果入栈。
 

------------
```cpp
#include<iostream>
#include<cstring>
#include<string> 
#include<stack>
 
using namespace std;
 
void read();
void cal(string s);
 
struct Matrix
{
	int x;
	int y;
	Matrix(){}
};
 
const int MAXN = 26 + 4;
 
Matrix m[MAXN];
 
int main()
{
	memset(m, 0, sizeof(m)); //初始化m
	int n;
	cin >> n;
	getchar();
	while (n--)
	{
		read();//读入输入给得n个矩阵
	}
	string s;
	while (cin >> s)
	{
		cal(s);//计算矩阵链乘表达并输出 
	}
	return 0;
}
 
 
void cal(string s)
{
	int sum = 0;
	stack<Matrix> st;
	if (s.length() == 1)  //如果只有一个矩阵，则计算次数为0 
	{
		cout << sum << endl;
		return;
	}
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
			continue;
		else if (s[i] == ')') //遇到')'需要计算栈内最上层的两个矩阵 
		{
			Matrix a, b, t;
			b = st.top(); st.pop();//后入的先出
			a = st.top(); st.pop();
			if (a.y != b.x) 	//无法计算 
			{
				cout << "error" << endl;
				return;
			}
			else     			//计算生成的新矩阵然后放入栈中 
			{
				t.x = a.x;
				t.y = b.y;
				st.push(t);
				sum += a.x * a.y * b.y;
			}
		}
		else
			st.push(m[s[i] - 'A']);
	}
	cout << sum << endl;
}
 
void read()
{
	string s;
	int a,b;
	cin >> s >> a >> b;
	m[s[0] - 'A'].x = a;
	m[s[0] - 'A'].y = b;
}
```



---

## 作者：happy_dengziyue (赞：1)

### 1 思路

##### 矩阵乘法

本题就是[矩阵乘法](https://baike.baidu.com/item/%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95/5446029?fr=aladdin)的经典题。

首先，设 $2$个矩阵为 $A$ 和 $B$。其中，$A$ 是 $x_1$ 行 $y_1$ 列的，$B$ 是 $x_2$ 行 $y_2$ 列的。

那么，如果 $y_1\ne x_2$，这 $2$ 个矩阵就不能相乘，直接输出 `error` 得了。

否则，它们所需的相乘次数为 $x_1\times y_1\times y_2$。

##### 栈

本题中，我们可以用栈来解决问题。

遍历一遍字符串，会有以下情况：

+ 当前是一个左括号：

	将左括号压入栈中。

+ 当前是一个字母（矩阵）：

	设 $N$ 为这个矩阵。

	+ 现在栈是空的：
    
		将 $N$ 压入栈中。
        
   + 现在栈不是空的：
   
   		+ 栈顶是一个左括号：
        
       		将 $N$ 压入栈中。
            
		 + 栈顶是一个矩阵：
         
         	设这个矩阵为 $F$，计算 $F\times N$ 的尺寸，把原来的栈顶弹出后把新的矩阵压入栈中，同时累加好计算次数。

+ 当前是右括号

	此时栈顶肯定有一个矩阵，设它为 $N$，并将它弹出栈，当然记得记录。然后，此时栈顶肯定是一个左括号，直接弹出它。
    
   + 现在栈是空的：
   
   	 将 $N$ 重新压入栈中。
     
   + 现在栈不是空的：
   
   		+ 栈顶是一个左括号：
        
       		将 $N$ 压入栈中。
            
		 + 栈顶是一个矩阵：
         
         	设这个矩阵为 $F$，计算 $F\times N$ 的尺寸，把原来的栈顶弹出后把新的矩阵压入栈中，同时累加好计算次数。
            
然后就输出，注意 `error` 的记录。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
struct M{//矩阵机构体
	long long x;//行数
	long long y;//列数
};
int n;//矩阵数
M a[28];//矩阵行数与列数
char c[10002];//运算
int cl;//运算长度
stack<M>s;//1到26为矩阵，0为左括号
M now;//当前
M fro;//栈顶
long long ans;//答案
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA00442_1.in","r",stdin);
	freopen("UVA00442_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%s%lld%lld",c,&a[i].x,&a[i].y);
	}
	while(scanf("%s",c)!=EOF){
		cl=strlen(c);
		while(!s.empty())s.pop();
		ans=0;
		for(int i=0;i<cl;++i){
			if(c[i]=='('){//左括号
				s.push((M){0,0});
				continue;
			}
			if(c[i]>='A'&&c[i]<='Z'){//字母
				now=(M){a[c[i]-'A'+1].x,a[c[i]-'A'+1].y};
				if(s.empty()){
					s.push(now);
					continue;
				}
				fro=s.top();
				if(fro.x==0&&fro.y==0){//括号
					s.push(now);
					continue;
				}
				if(fro.y!=now.x){//有问题
					ans=-1;
					break;
				}
				s.pop();
				ans+=fro.x*fro.y*now.y;
				s.push((M){fro.x,now.y});
			}
			else{//右括号
				now=s.top();
				s.pop();
				s.pop();//把一个左括号弹出
				if(s.empty()){
					s.push(now);
					continue;
				}
				fro=s.top();
				if(fro.x==0&&fro.y==0){
					s.push(now);
					continue;
				}
				if(fro.y!=now.x){//有问题
					ans=-1;
					break;
				}
				s.pop();
				ans+=fro.x*fro.y*now.y;
				s.push((M){fro.x,now.y});
			}
		}
		if(ans==-1)printf("error\n");
		else printf("%lld\n",ans);
		fflush(stdout);
	}
}
```

[记录传送门](https://www.luogu.com.cn/record/53599525)

By **dengziyue**

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
**矩阵乘法**就是设 $A$ 为 $m \times p$ 的矩阵，$B$ 为 $p \times n$ 的矩阵，结果就是： $m \times p \times n$ 。题目过程其实不难，就是每次碰到字母就把字母对应的表达式插入到栈里面；当碰到 `)` 就代表一段计算的结尾，于是就取出栈顶的两个表达式进行计算，当 $p$ 出现不相等时，就输出 `error`。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 2147483647;
int n, ans = 0;
string s;
struct Node {
  char s;
  int a, b;
} e[30];
int w_x(char s) {
  for (int i = 1; i <= n; i++) {
    if (e[i].s == s) {
      return i;
    }
  }
  return -INF;
}

struct Node2 {
  int a, b;
};
stack<Node2> st;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].s >> e[i].a >> e[i].b;
  }
  while (cin >> s) {
    ans = 0;
    //设A为 m * p 的矩阵，B 为 p * n 的矩阵 总面积： m * p * n 。
    while (!st.empty()) {
      st.pop();
    }
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        continue;
      } else if (s[i] == ')') {
        int ya = st.top().a;
        int yb = st.top().b;
        st.pop();
        int xa = st.top().a;
        int xb = st.top().b;
        st.pop();
        if (xb == ya) {
          ans = ans + xa * xb * yb;
          st.push(Node2{xa, yb});
        } else {
          ans = -INF;
          break;
        }
      } else {  //字母
        st.push(Node2{e[w_x(s[i])].a, e[w_x(s[i])].b});
        }
    }
    if (ans == -INF) {
      cout << "error\n";
    } else {
      cout << ans << "\n";
    }
  }
  return 0;
}
```

---

## 作者：KingOfWA (赞：0)

[俺的博客](http://pipe.b3log.org/blogs/cms42/articles/2019/07/24/1563960533130)食用效果更佳

非标准解法：递归  ~~（虽然我明知道这是栈处理表达式的裸题）~~

其实不用自定义结构体,`"typedef Mat pair<int,int>"`搞定

```cpp
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

typedef pair<int,int> Mat;
Mat a[30]; //储存字母对应的矩阵
int n,x,y;
char c;
string s;
int ps,ls; //ls:字符串s的长度 ps:字符串s的指针

int solve(Mat& t){ //Mat为乘法运算后的矩阵，返回值为当前运算次数
    char c;
    Mat x(0,0),y(0,0);
    int x1=0,y1=0,ans=0;
    if(ps==ls) return 0;
    c=s[++ps];
    if(c=='('){//左括号，递归处理
        x1=solve(x);
        if(x1==-1) return -1;
        ++ps;//右括号
    }
    else if(c==')'){
        --ps;//必须由其上一层函数处理右括号，想一想为什么
        return 0;
    }
    else{
        x=a[c-'A'];
    }
    if(ps==ls){
        t=x;
        return x1;
    }
    c=s[++ps];
    if(c=='('){//左括号，递归处理
        y1=solve(y);
        if(y1==-1) return -1;
        ++ps;//右括号
    }
    else if(c==')'){
        --ps; //必须由其上一层函数处理右括号，想一想为什么
        t=x;
        return x1; //注意这里不能返回0，因为第一个参数可能是一个子运算，可能已有运算次数
    }
    else{
        y=a[c-'A'];
    }
    if(x.second!=y.first) return -1;//error
    ans=x1+y1+x.first*x.second*y.second;
    t.first=x.first;
    t.second=y.second;
    return ans;
}

int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> c >> x >> y;
        a[c-'A'].first=x;
        a[c-'A'].second=y;
    }
    while(cin >> s){
        ps=-1; ls=s.length()-1;
        Mat t(0,0);
        int res=solve(t);
        if(res==-1) cout << "error\n";
        else cout << res << "\n";
    }
    return 0;
}
```

---

## 作者：Clyfort (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA442)
---
- 这个题目需要了解一下 EBNF，这个是编程书籍中常用的一种语法规则，通常结合自然语言以伪代码的形式展现出来。

- 矩阵乘法，假设两个矩阵相乘，

  其中一个矩阵 $M_1$ 是 $r_1$ 行 $c_1$ 列

  另一个矩阵 $M_2$ 是 $r_2$ 行 $c_2$ 列

  那么 $M_1 \times M_2$ 的计算次数是 $r_1 \times c_1 \times c_2$

---

如果理解了题目中 EBNF 的意思和学会了矩阵乘法，那么这个题目就是按题目意思模拟这个过程。

# $Code$
```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 3e2 + 5;
struct matrix
{
    ll r,c;
} mt[maxn];

int n;
ll ans;
stack<matrix> s;
string str;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)
    {
        char ch;
        int r, c;
        cin >> ch >> r >> c;
        mt[ch].r = r;
        mt[ch].c = c;
    }
    getchar();	//一定要注意！！！
    while (getline(cin, str))
    {
        ans = 0;
        int flag = 0;
        for (int i = 0; i < str.size(); i ++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
                s.push(mt[str[i]]);
            else if (str[i] == ')')
            {
                matrix a, b;
                b = s.top(); s.pop();
                a = s.top(); s.pop();
                if (a.c != b.r)
                {
                    flag = 1;
                    break;
                }
                ans += a.r * a.c * b.c;
                s.push(matrix{a.r, b.c});
             }
        }
        if (flag == 1)
            puts("error");
        else
            cout << ans << endl;
    }
	return 0;
}
```

---

## 作者：WanderingTrader (赞：0)

感谢尊敬管理员们通过我的第一篇题解，希望这篇也能通过。  
括号有关的题目，自然是用“栈”来解决。  
题目中已经说明，凡三连矩阵都不能直接计算，需要括号辅助。  
这也就意味着，只要看到右括号，就把栈内的两矩阵弹出并计算，全部模拟一遍即可。  
此题主要是要注意一些细节，我在下面代码中的注释给出。  
AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 30
typedef pair<int,int> P;
string s; 
P m[N];		//记录矩阵信息
int temp = 1; 
bool live = true;		//表示能否链接
stack<P> st;
int main()
	int n,cnt=0;
	char c;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>c;
		cin>>m[c-'A'].first>>m[c-'A'].second;	//存储
	}
	while(cin >> s){
		cnt = 0;
		int l = s.length();
		live = true;
		for(int i = 0;i < l;i ++)
		{
			if(s[i] == ')'){ 
				P b = st.top();
				st.pop();
				P a = st.top();
				st.pop();				//注意是先b后a
				if(b.first == a.second) //能连接就连接,并修改最终答案
				{
					st.push({a.first,b.second});
					cnt += a.first * a.second * b.second;
				}
				else 					//不能连接就改为false
					live = false;
			}
			else if(isalpha(s[i]))		//是字母就压入栈
				st.push({m[s[i]-'A'].first,m[s[i]-'A'].second});
		}
		if(live)
			cout<<cnt<<endl; 
		else
			cout<<"error"<<endl;		//输出答案
	}
	return 0;
}
```

---

## 作者：Zlc晨鑫 (赞：0)

$Update:2020.4.30$：美化了一些公式。

---

[$\text{My blog}$](https://www.luogu.com.cn/blog/Zlc/)  
[题目传送门](https://www.luogu.com.cn/problem/UVA442)  
[AC记录](https://www.luogu.com.cn/record/32900682)

---

题意理解：
- 本题可以使用栈来解析表达式；
- 因为输入保证合法，所以左括号不用入栈；
- 似乎一个括号里的表达式只有两个字母。

---

表达式的运算规则：
- 例如：$A=(10, 20), B=(20, 30)$，则$A \times B = 10 \times 20 \times 10$，也就是$\text{A的第一个元素} \times \text{A和B共同的元素} \times \text{B的第二个元素}$；

- 若A的第二个元素和B的第一个元素不同，则计算无法进行。

--- 

若使用`scanf`读入，本题需要这样写：
```cpp
scanf("%d\n", &n);
scanf("%c %d %d\n", &ch, &a, &b);
```
注意那个`'\n'`，因为`scanf`会读换行和空格，所以要在缓冲区中把`'\n'`读掉，不然`ch`读到的就是`'\n'`而不是一个大写字母；还有就是`%c`和`%d`之间的空格，这样做也是为了过滤空格。

要解决这个问题，除了上面这种写法，还可以采用`cin`输入，当然前提是题目不用读空格和换行。

还有就是，需要注意先出栈的是`b`，然后才是`a`。

---

AC代码：

```cpp
#include <stack>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

struct M {
    int a, b;
    M(const int& a = 0, const int& b = 0) :a(a), b(b) {}
}value[26];

int main() {
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
        char ch;
        int a, b;
        scanf("%c %d %d\n", &ch, &a, &b);
        value[ch - 'A'] = M(a, b);
    }
    string str;
    while (cin >> str) {
        stack<M> s; //用于解析表达式的栈
        bool err = false;
        int ans = 0;
        for (int i = 0, len = str.size(); i < len; ++i)
            if (str[i] >= 'A' && str[i] <= 'Z')
                //如果是字母就将其对应的值入栈
                s.push(value[str[i] - 'A']);
            else if (str[i] == ')') {
                //如果是右括号就计算结果的值并再次将新矩阵入栈
                M b(s.top()); s.pop();
                M a(s.top()); s.pop(); //注意此处先出栈的是b
                //如果无法进行计算
                if (a.b != b.a) { err = true; break; }
                ans = ans + a.a * a.b * b.b;
                s.push(M(a.a, b.b)); //新矩阵入栈
            }
        err ? puts("error") : printf("%d\n", ans);
    }
    return 0;
}
```

---

如有错误欢迎指出，谢谢阅读。

---

