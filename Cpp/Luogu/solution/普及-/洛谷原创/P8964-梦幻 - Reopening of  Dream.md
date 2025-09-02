# 梦幻 | Reopening of  Dream

## 题目背景

_望你没有因此而功亏一篑过_

花开不是为了花落，而是为了更加灿烂。

最初拥有的只是理想和自信，但所有的一切都从这里交错着生长，在努力与汗水铺成的路上走下去不会是错误的选择——至少你为此喜怒哀乐过。

**祝每一位有理想的参赛者都能取得理想的成绩！**


## 题目描述

PION2202 的选手代码公布了。作为一个~~连续编写了十年迷惑行为大赏~~的人，你当然是要抢先把代码中的各种事迹发出来啦。

首先关注的肯定是大家的文件输入输出有没写对。你已经让小 E 把每道题的题目名称和每位选手的 `freopen` 语句整理出来了。

PION2202 一共有 $m$ 道题，有 $n$ 位选手参与。你决定把选手分成三类：

1. 普通人：最正常不过的 `freopen` 语句；
2. 见祖宗人：被注释的 `freopen` 语句；
3. 乐子人：其他形式的 `freopen` 语句。

形式化地，普通人的所有题目的 `freopen` 语句都应该恰好是

```cpp
freopen("<title>.in","r",stdin);
freopen("<title>.out","w",stdout);
```

其中的 `<title>` 应替换成对应的题目名称。

见祖宗人的 `freopen` 语句中存在至少一道题的至少一行语句以 `//freopen(` 开头，以 `);` 结尾。

如果一位选手的 `freopen` 语句不满足上面两种情况，则称这位选手为乐子人。

你需要判断每位选手是普通人，见祖宗人还是乐子人。

## 说明/提示

**【样例解释】**

第一位选手所有的 `freopen` 语句都很正常，所以是普通人。

第二位选手注释了题目 `woem` 的输入文件语句，所以是见祖宗人。虽然该选手在题目 `kcarrab` 中有乐子行为但由于已经满足了见祖宗人的条件，所以该选手被分类为见祖宗人。

第三位选手四道题的 `freopen` 语句都不是正常的。`tnalp` 的输出文件语句少了分号；`woem` 被打成了 `owem`；打反了 `kcarrab` 一题中的 `stdin` 和 `stdout`；交换了 `hctam` 的两个语句的顺序。在本题中算作乐子人。

第四位选手的 `freopen` 语句虽然能够正常工作，但是因为与正常的 `freopen` 语句不同而在本题中被算作乐子人。

---

**【数据范围】**

**本题采用捆绑测试。**

子任务 1（30 分）：$T = 1$。$m = 1$ 且题目名称为 `yxalag`。但是，如果你输出 `No, general!` 是不能得到分数的。  
子任务 2（30 分）：$T = 2$。保证没有见祖宗人。  
子任务 3（40 分）：$T = 3$。无特殊性质。

对于 $100\%$ 的数据：

- 保证 $1\le T \le 3$。
- 保证 $1\le n\le 1000$。
- 保证 $1\le m \le 4$。
- 保证题目名称的长度在 $1$ 到 $10$ 之间。
- 保证每一行 `freopen` 语句的长度在 $1$ 到 $100$ 之间。

## 样例 #1

### 输入

```
3
4 4
tnalp
woem
kcarrab
hctam

freopen("tnalp.in","r",stdin);
freopen("tnalp.out","w",stdout);
freopen("woem.in","r",stdin);
freopen("woem.out","w",stdout);
freopen("kcarrab.in","r",stdin);
freopen("kcarrab.out","w",stdout);
freopen("hctam.in","r",stdin);
freopen("hctam.out","w",stdout);

freopen("tnalp.in","r",stdin);
freopen("tnalp.out","w",stdout);
//freopen("woem.in","r",stdin);
freopen("woem.out","w",stdout);
freopen("kcarrab.in","r",stdin);
//I_AK_IOI!!!
freopen("hctam.in","r",stdin);
freopen("hctam.out","w",stdout);

freopen("tnalp.in","r",stdin);
freopen("tnalp.out","w",stdout)
freopen("owem.in","r",stdin);
freopen("woem.out","w",stdout);
freopen("kcarrab.in","r",stdout);
freopen("kcarrab.out","w",stdin);
freopen("hctam.out","w",stdout);
freopen("hctam.in","r",stdin);

freopen("tnalp.in","r",stdin);//I_LOVE_CCF
freopen("tnalp.out","w",stdout);
freopen("woem.in","r",stdin);//I_HATE_THIS
freopen("woem.out","w",stdout);
freopen("kcarrab.in"/*I_FORGET_HOW_TO_FIND_BRIDGES!!!!!!*/,"r",stdin);
freopen("kcarrab.out","w",stdout);
freopen("hctam.in","r",stdin);//I_CAN_GET_ONLY_8PTSqwq
freopen("hctam.out","w",stdout);
```

### 输出

```
PION2202 RP++.
Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.
Good luck and have fun.
Good luck and have fun.
```

# 题解

## 作者：Infinite_Eternity (赞：13)

$\large\textbf{梦幻 | Reopening of Dream}$
------------

按题意模拟即可。

由于不知道每个 `<title>` 的长度为多少，以及为了避免忘记清空 `char` 数组，推荐使用 `string` 类型。

```cpp
string title[4],read,write;
```
> 其中，$\text{title}$ 是每道题目的名称，$\text{read}$ 指选手的 `freopen("<title>.in","r",stdin);` 语句，$\text{write}$ 指选手的 `freopen("<title>.out","w",stdout);` 语句。

**我们将普通人作为 $\text{type 1}$，将乐子人作为 $\text{type 2}$，将见祖宗人作为 $\text{type 3}$。（原因会在下文中解释）**

- 对于 $\text{type 1}$，我们需要使得 $\text{read}$ 和 $\text{write}$ 皆与正确语句一模一样：（由于字符串可以拼接的特性，我们可以用 `+` 进行连接。其中，`\` 是转义符。）

```cpp
if ((read == "freopen(\"" + title[j] + ".in\",\"r\",stdin);") && (write == "freopen(\"" + title[j] + ".out\",\"w\",stdout);"))
	each_type = 1;
```

------------

在讲解 $\text{type 3}$ 之前，我们先补充一下 $\text{substr()}$ 函数的用法：

假设 `string s = "E_Space_is_amazing";`

- `string sub1 = s.substr(11)` 表示：从下标为 $11$ 的字符开始，一直取到结尾，则 `sub1 = "amazing"`；

- `string sub2 = s.substr(11,3)`表示：从下标为 $11$ 的字符开始，截取长度为 $3$ 的子串，则 `sub2 = "ama"`；

特别地：

- 若开始字符的下标超过了 $s.\text{length()}$，则 $\text{substr()}$ 函数会返回 `terminate called after throwing an instance of 'std::out_of_range'`；
- 若开始字符的下标与截取长度的和超过了 $s.\text{length()}$，则 $\text{substr()}$ 函数将截取到 `string s` 的末尾后自动停止。

------------

- 对于 $\text{type 3}$，我们需要使得 $\text{read}$ 和 $\text{write}$ 中**至少有一句**以 `//freopen(` 开头，以 `);` 结尾：（切记，需要与题目描述一致，不可只判断是否以 `//` 开头）

```cpp
else if ((read.substr(0, 10) == "//freopen(") && (read.substr(read.length()-2) == ");") || 
        (write.substr(0, 10) == "//freopen(") && (write.substr(write.length()-2) == ");"))
	each_type = 3;
```

值得一提的是，注意到在判断语句 `(read.substr(read.length()-2) == ");")` 中：当 `read.length() < 2` 时，会引起 Runtime Error；但是当 `read.length() < 2` 时，`(read.substr(0, 10) == "//freopen(")` 必然不成立，构成 `&&` 短路，于是不会 Runtime Error。

**最后，我们来解释一下本题的优先级，同时回答上文的问题。**

- 在同时出现普通行为和乐子行为时，我们优先考虑乐子行为，即：$\text{type 1 < type 2}$；
- 在同时出现普通行为和见祖宗行为时，我们优先考虑见祖宗行为，即：$\text{type 1 < type 3}$；
- 在同时出现乐子行为和见祖宗行为时，我们优先考虑见祖宗行为，即：$\text{type 2 < type 3}$；

**综上，$\text{type 1 < type 2 < type 3}$。这样，代码的实现便容易了许多。**

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,m;
string title[4],read,write;
inline int max(int a,int b)
{
    return (a>b) ? a : b;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin >> T >> n >> m;
    for (register int i=0; i<m; ++i)
    {
        cin >> title[i];
    }
    for (register int i=0; i<n; ++i)
    {
        int type=1;
        for (register int j=0; j<m; ++j)
        {
            int each_type=2;
            cin >> read >> write;
            if ((read == "freopen(\"" + title[j] + ".in\",\"r\",stdin);") && (write == "freopen(\"" + title[j] + ".out\",\"w\",stdout);"))
                each_type = 1;
            else if ((read.substr(0, 10) == "//freopen(") && (read.substr(read.length()-2) == ");") || (write.substr(0, 10) == "//freopen(") && (write.substr(write.length()-2) == ");"))
                each_type = 3;
            type=max(type,each_type);
        }
        if (type == 1)
            puts("PION2202 RP++.");
        else if (type == 3)
            puts("Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.");
        else
            puts("Good luck and have fun.");
    }
    return 0;
}
```

Ps. 感谢 [Cloud_yx](/user/743416) 对 $\text{substr()}$ 函数的用法的补充。

---

## 作者：Convergent_Series (赞：7)

梦幻 | Reopening of Dream 题解
---
### 知识： ``substr`` 函数
+ 用法： ``a.substr(int pos,int n)`` 。
+ 解释：返回 ``string`` 类型参数，包含 $a$ 中从 $pos$ 开始的 $n$ 个字符的拷贝（ $pos$ 的默认值是 $0$ ，$n$ 的默认值是 `s.size() - pos` ，即不加参数会默认拷贝 $a$ ）。
+ 补充：若 $pos$ 的值超过了 ``a.length()`` ，则 ``substr`` 函数会返回 ``terminate called after throwing an instance of 'std::out_of_range'`` ；若 $pos+n>$ ``a.length()``  ，则 ``substr`` 会调整 $n$ 的值，只拷贝到 $a$ 的末尾。

---
## 判断思路：

编写函数 ``int work(int k)`` 代表某人第 $k$ 题的代码类型，返回值为 $1\sim3$ 之间的正整数。
### 1.普通人
普通人的 ``freopen`` 一定与标准格式完全相同，所以只需要拼接出标准代码，比较即可。
```cpp
fra="freopen(\""+name[k]+".in\",\"r\",stdin);";
frb="freopen(\""+name[k]+".out\",\"w\",stdout);";
if(a==fra&&b==frb) return 1;
//string可以直接用 + 连接，= 赋值，== 比较。
```
### 2.见祖宗人
分别用 ``substr`` 取出两句代码的 $0\sim9$ 、 $len-2\sim len-1$ 位，判断即可。
```cpp
if(a.substr(0,10)=="//freopen("&&a.substr(a.length()-2,2)==");") return 2;
if(b.substr(0,10)=="//freopen("&&b.substr(b.length()-2,2)==");") return 2;
```
### 3.乐子人
如果还没有 ``return`` 就一定是乐子人。
```cpp
return 3;
```
---
## 数据处理
先读入 $T ,n, m$ 和 题目名称。  
对于每一个选手，用桶 $a$ 存储每一种情况出现的次数。 

如果 $a[1]=m$ ，则该选手为普通人。  
如果 $a[2]\ge1$ ，则该选手为见祖宗人。  
否则就是乐子人。
```cpp
for(i=1;i<=n;i++){
	a[1]=a[2]=a[3]=0;
	for(j=1;j<=m;j++) a[work(j)]++;
	if(a[1]==m)
		printf("PION2202 RP++.\n");
	else if(a[2]!=0)
      printf("Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.\n");
	else printf("Good luck and have fun.\n");
}
```
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string name[10];
int work(int k){
	string a,b;
	string fra,frb;
	int i=0,j,ss;
	fra="freopen(\""+name[k]+".in\",\"r\",stdin);";
	frb="freopen(\""+name[k]+".out\",\"w\",stdout);";
	cin>>a>>b;
	if(a==fra&&b==frb) return 1;
 	if(a.substr(0,10)=="//freopen("&&a.substr(a.length()-2,2)==");") return 2;
	if(b.substr(0,10)=="//freopen("&&b.substr(b.length()-2,2)==");") return 2;
	return 3; 
}
int main()
{
	int t;
	cin>>t;
	scanf("%d %d",&n,&m);
	int i,j,a[5];
	for(i=1;i<=m;i++) cin>>name[i];
	for(i=1;i<=n;i++){
		a[1]=a[2]=a[3]=0;//每一次都要清0
		for(j=1;j<=m;j++) a[work(j)]++;
		if(a[1]==m){
			printf("PION2202 RP++.\n");
		}else if(a[2]!=0){
			printf("Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.\n");
		}else printf("Good luck and have fun.\n");
	}
	return 0;
}
```

---

## 作者：1qaz234Q (赞：3)

### 题意简述
一共有 $m$ 道题，有 $n$ 位选手参与。如果选手的代码是最正常不过的 freopen 语句，输出 `PION2202 RP++.`。如果选手的代码以 `//freopen(` 开头，以 `);` 结尾，输出 `Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.`。
否则输出 `Good luck and have fun.`。
### 题目分析
- 输入 $T,n,m$。循环 $m$ 次，输入题目名称，拼接 freopen 语句，用二维数组 $a$ 存储 freopen 语句。
- 循环 $n$ 次。变量 $g$ 表示选手的分类，初始值为普通人。循环 $m$ 次，用字符串储存选手的 freopen 输入和输出语句，用 substr 取字符串的前 $10$ 个字符。如果变量 $g$ 表示的不是见祖宗人。再判断当前 freopen 语句，如果当前 freopen 语句为见祖宗人写的，$g$ 改为见祖宗人。如果当前 freopen 语句为乐子人写的，$g$ 改为乐子人。
- 判断 $g$ 的值。如果 $g$ 为普通人，输出 `PION2202 RP++.`。如果 $g$ 为见祖宗人，输出 `Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.`。如果 $g$ 为乐子人，输出 `Good luck and have fun.`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;
string a[N][2];//存储所有题目的正常freopen语句
signed main(){
    int t,n,m;
    cin>>t>>n>>m;
    for(int i=1;i<=m;i++){
    	string b;
    	cin>>b;
    	a[i][0]="freopen(\""+b+".in\",\"r\",stdin);";//拼接freopen输入语句
    	a[i][1]="freopen(\""+b+".out\",\"w\",stdout);";//拼接freopen输出语句
	}
	while(n--){
		int g=2;//g=0时表示乐子人，g=1时表示见祖宗人，g=2时表示普通人
		for(int i=1;i<=m;i++){
			string c,d;
			cin>>c>>d;
			string e=c.substr(0,10),f=d.substr(0,10);//e表示c的前10个字符，f表示d的前10个字符
			if(g!=1){
				if(e=="//freopen("&&c[c.size()-2]==')'&&c[c.size()-1]==';'||f=="//freopen("&&d[d.size()-2]==')'&&d[d.size()-1]==';'){//如果freopen语句以“//freopen(”开头，以“);”结尾
					g=1;
				}
				else if(c!=a[i][0]||d!=a[i][1]){//如果freopen语句不正常
					g=0;
				}
			}
		}
		if(g==0){//如果选手为乐子人
			puts("Good luck and have fun.");
		}
		if(g==1){//如果选手为见祖宗人
			puts("Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.");
		}
		if(g==2){//如果选手为普通人
			puts("PION2202 RP++.");
		}
	}
}
```

---

## 作者：Lovely_Elaina (赞：2)

注：本题简单，故本篇题解不带有任何废话。

---

### 思路

先看题目再来。

提示：

- 不要忘了输入子任务编号 `T`。

共有三种类型（type）：

- t1：最正常不过的 `freopen` 语句；
- t2：被注释的 `freopen` 语句；
- t3：其他形式的 `freopen` 语句。

先在读入的时候，将每个题目的 t1 标准形式给存来。

然后在后面输入每位选手的 `freopen` 时，定义 $2$ 个 bool 类型的变量（b1,b2）。

- 初始定义 b1 为 true，输入时，如有一题不符 t1 标准，则改为 false；
- 初始定义 b2 为 false，输入时，如不符合 t1 标准就判断，如果符合 t2 标准则改为 true。

输入完后判断：

- 如果 b1 为 true，普通人；
- 如果 b1 不为 true，b2 为 true，就是见祖宗人；
- 如果 b1 和 b2 同时为 false，就是乐子人。

### 代码

理论存在，实践开始。

注意点（都是我出现了问题的捏）：

1. 存 `freopen` 输入输出的 t1 形式时不要打错；
2. 判断是否为 t2 形式时，substr 一定要打对。

输入时存 `freopen` 的输入和输出 t1 形式：

```cpp
cin >> T >> n >> m;
for(int i = 1; i <= m; i++){
    cin >> t[i];
    t1[i] = "freopen(\"" + t[i] + ".in\",\"r\",stdin);"; // t1形式
    t1[4+i] = "freopen(\"" + t[i] + ".out\",\"w\",stdout);"; // t1形式
    //cout << t1[i] << endl;
}
```

判断是否为 t2 形式：

```cpp
bool t2(string s){
    if(s.substr(0,10) == "//freopen(" && s.substr(s.size()-2) == ");")
        return true;
    return false;
}
```

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int M = 10;

int T,n,m;    // 如题
string t[M];  // 名称
string t1[M]; // t1形式

// 判断是否为t2类型
bool t2(string s){
    if(s.substr(0,10) == "//freopen(" && s.substr(s.size()-2) == ");")
        return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> T >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> t[i];
        t1[i] = "freopen(\"" + t[i] + ".in\",\"r\",stdin);"; // t1形式
        t1[4+i] = "freopen(\"" + t[i] + ".out\",\"w\",stdout);"; // t1形式
        //cout << t1[i] << endl;
    }

    string s1,s2;
    while(n--){
        bool b1 = true,b2 = false;
        for(int i = 1; i <= m; i++){
            cin >> s1 >> s2;
            //cout << s1 << " " << s2 << endl;
            if(s1 != t1[i] || s2 != t1[4+i]){
                //cout << s1 << " | " << s2 << endl;
                //cout << t1[i] << " | " << t1[4+i] << endl;
                b1 = false;
                if(t2(s1) || t2(s2))
                    b2 = true;
            }
        }
        if(b1) cout << "PION2202 RP++." << endl;
        else if(b2) cout << "Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI." << endl;
        else cout << "Good luck and have fun." << endl;
    }
    return 0;
}
```

---

## 作者：xiaoqian02 (赞：1)

### 第一部分：大概思路
~~怎么会有 Div2 T1 就是模拟的月赛~~

首先，输入的 $T$ 实际上没什么用，读一下就可以了。

对于每道题，可以用两个字符串保存这道题正确的 `freopen` 写法（一个 `stdin`，一个 `stdout`）。

对于每一个人，我们先暂且认为他是普通人。用一个变量 $tp$ 存储这个人的类型，`0` 为普通人，`1` 为见祖宗人，`2` 为乐子人。

接下来，对于每道题的 `freopen`，一个一个判断。

- 如果这个人已经是见祖宗人了，不用判，直接 `continue;`。见祖宗人的优先级最高。

- 否则，将这个人的语句与存下来的标准语句比较。如果完全相同，说明这一句是正确的，不用操作。

- 如果这个人的代码符合见祖宗人的条件，就将 $tp$ 赋值为 $1$。

- 最后，如果还没退掉，说明至少在这段代码上，这个人是乐子人，所以将 $tp$ 赋为 $2$。

最后直接对照着输出就好了。

说一下见祖宗人的简易判断方式：用字符串查找子串位置，从左边找 `//freopen(`，从右边找 `);`。具体看下面的代码。
### 第二部分：代码
~~喜闻乐见的东西~~

有一部分是调试代码，但不影响。

忠告：输出的字符串建议复制粘贴，不要手打，容易错。
```cpp
#include<bits/stdc++.h>
#define yh '"'
using namespace std;
int x,T,pr;
string stdk[5][2];
string s;
int tp;
int main()
{
	//cout<<int('"')<<endl;
	cin>>x;
	cin>>T>>pr;
	for(int i=1;i<=pr;i++)
	{
		cin>>s;//之后一大段都是保存标准 freopen 代码
		stdk[i][0]="freopen(";
		stdk[i][0]+=yh;
		stdk[i][0]+=s;
		stdk[i][0]+=".in";
		stdk[i][0]+=yh;
		stdk[i][0]+=',';
		stdk[i][0]+=yh;
		stdk[i][0]+='r';
		stdk[i][0]+=yh;
		stdk[i][0]+=',';
		stdk[i][0]+="stdin";
		stdk[i][0]+=");";
		//---------------------------
		stdk[i][1]="freopen(";
		stdk[i][1]+=yh;
		stdk[i][1]+=s;
		stdk[i][1]+=".out";
		stdk[i][1]+=yh;
		stdk[i][1]+=',';
		stdk[i][1]+=yh;
		stdk[i][1]+='w';
		stdk[i][1]+=yh;
		stdk[i][1]+=',';
		stdk[i][1]+="stdout";
		stdk[i][1]+=");";
	}
	//for(int i=1;i<=2*pr;i++) cout<<stdk[(i+1)>>1][1-i%2]<<endl;
	while(T--)
	{
		tp=0;
		for(int i=1;i<=2*pr;i++)
		{
			cin>>s;
			//cout<<(s==stdk[(i+1)>>1][1-i%2])<<endl;
			if(tp==1) continue;//已经是见祖宗人了
			if(s==stdk[(i+1)>>1][1-i%2]) continue;
			if(s.find("//freopen(")==0&&s.rfind(");")==s.size()-2) tp=1;//见祖宗人
            else tp=2;//否则是乐子人
		}
		if(tp==0) cout<<"PION2202 RP++."<<endl;
		else if(tp==1) cout<<"Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI."<<endl;
		else cout<<"Good luck and have fun."<<endl;
	}
	return 0;
}
```
### 第三部分：忠告
十年 OI 一场空，注释 freopen 见祖宗。

---

## 作者：GoldenCreeper (赞：1)


一道非常 ~~水~~ 好的字符串模拟题。

帮助各位新人 Oler 熟悉 `string` 类型的用法。

------------
**易错点**

根据样例解释 我们可以知道：如果一个人既满足乐子人，也满足见祖宗人，那么应该算见祖宗人。


------------

- 对于正常人，他的 `freopen` 应该与正确语句一样，因为本题输入不含空格，所以判断语句为：
```
string ca = "freopen(\""+name[j]+".in\",\"r\",stdin);";// \为转义符 name[j] 表示文件名字
string cb = "freopen(\""+name[j]+".out\",\"w\",stdout);";
if (ca == a && cb == b) f1 = 1; // f1 用来判断是否是正常人
```
- 对于见祖宗人，应该判断 `freopen` 是否被注释。
```
string ca = "freopen(\""+name[j]+".in\",\"r\",stdin);";
string cb = "freopen(\""+name[j]+".out\",\"w\",stdout);";
if (a == ca && b == cb) f1 = true;
if ((a.substr(0,10) == "//freopen(") || (b.substr(0,10) == "//freopen(")) f2 = true; //f2 表示是否是见祖宗人
```
~~其实不只应该判断前面是不是~~`//freopen`~~，还应该判断后面有没有~~`);`~~，但不知道为啥不加也能过~~。

- 判断完上面两种，剩下的就是乐子人啦。

```
string ca = "freopen(\""+name[j]+".in\",\"r\",stdin);";
string cb = "freopen(\""+name[j]+".out\",\"w\",stdout);";
if (a == ca && b == cb) f1 = true;
if ((a.substr(0,10) == "//freopen(") || (b.substr(0,10) == "//freopen(")) f2 = true;
else f3 = true 
```
------------
最后附上 ACcode：
```
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int t,m,n;
string name[20];
int main(){
    scanf("%d%d%d",&t,&n,&m);
    for (int i = 1;i <= m;++i) cin >> name[i]; // 输入名字
    for (int i = 1;i <= n;++i){
        string a,b;
        bool f1 = 0,f2 = 0,f3 = 0;
        for (int j = 1;j <= m;++j){
            cin >> a >> b;
            string ca = "freopen(\""+name[j]+".in\",\"r\",stdin);";
            string cb = "freopen(\""+name[j]+".out\",\"w\",stdout);"; // 创建临时变量ca cb 方便后面的运算 但是我写完发现没方便多少（）
            if (a == ca && b == cb) f1 = true;
            if ((a.substr(0,10) == "//freopen(") || (b.substr(0,10) == "//freopen(")) f2 = true;
            else f3 = true;
        }
        if (f2 == false && f3 == true) printf("Good luck and have fun.\n");
        else if (f2 == true) printf("Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.\n");
        else printf("PION2202 RP++.\n");
    }
    return 0;
}
```

---

## 作者：hycqwq (赞：1)

## 思路

题目已经说的很清楚了，这里我再补充一点。

如果一位选手同时可能拥有多种身份，那么三种身份的优先级从大到小为：见祖宗人，乐子人，普通人。

所以我将三种身份在程序中处理的编号分别设为：

|身份|编号|
|:-:|:-:|
|普通人|$0$|
|见祖宗人|$2$|
|乐子人|$1$|

由于见祖宗人的判断是基于子串的，所以我们要先确保字符串长度大于  $10$（即 `//freopen(` 的长度）

另外，见祖宗人注释的 `freopen` 语句不一定要是正确的。如果你搞错了这一点，那么你只能得到 $30$ 分。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if

int t, n, m;
string title[5], fin, fout;

int main()
{
    cin >> t >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> title[i];
    for (int i = 1; i <= n; i++)
    {
        int type = 0;//0普通人 1乐子人 2见祖宗人
        //这样编号，后面在确定身份时就可以直接取max，不用考虑优先级
        for (int j = 1; j <= m; j++)
        {
            cin >> fin >> fout;
            if (fin == "freopen(\"" + title[j] + ".in\",\"r\",stdin);" && fout == "freopen(\"" + title[j] + ".out\",\"w\",stdout);")//普通人
                type = max(0, type);
            elif ((fin.size() >= 10 && fin.substr(0, 10) == "//freopen(" && fin.substr(fin.size() - 2) == ");") || (fout.size() >= 10 && fout.substr(0, 10) == "//freopen(" && fout.substr(fout.size() - 2) == ");"))//见祖宗人
                type = max(2, type);
            else//乐子人
                type = max(1, type);
        }
        if (type == 0)//普通人
            cout << "PION2202 RP++." << endl;
        elif (type == 2)//见祖宗人
            cout << "Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI." << endl;
        else//乐子人
            cout << "Good luck and have fun." << endl;
    }
    return 0;
}
```

---

## 作者：JuRuoOIer (赞：1)

# 题解 P8964 梦幻 | Reopening of Dream

Update on 2023.2.2：针对仅通过 subtask2 的代码给出了 hack（上一次提交时忘记给了）。

### Part1 题意

[原题传送门](https://www.luogu.com.cn/problem/P8964)

给定 $m$ 道题及 $n$ 个选手每一道题的 `freopen` 代码，将选手进行归类：
- 普通人：标准的 `freopen` 语句，即 `freopen("???.in","r",stdin);freopen("???.out","w",stdout);`。
- 见祖宗人：有至少一个语句以 `//freopen(` 开头，以 `);` 结尾。
- 乐子人：不属于以上两类的其他人。

$n\le1000,m\le4$，题目名称长度不超过 $10$，语句长度不超过 $100$，均只包含 ASCII 可见字符。

### Part2 思路

我们把三类人分开考虑。

- 普通人：既然给出了题目名称，那（题目中定义的）正常的 `freopen` 语句就可以确定了。我们可以在输入题目名称时预处理出正常的语句，所有语句都与正常语句相同即为普通人。我使用了字符串加法实现预处理的过程，代码如下：

```cpp
//ai、ao 为定义好的 string 型数组
ai[i]="freopen(\""+s+".in\",\"r\",stdin);";//注意 freopen 语句中的分号
ao[i]="freopen(\""+s+".out\",\"w\",stdout);";
```

- 见祖宗人：只需要判断是不是以 `//freopen(` 开头，以 `);` 结尾即可，使用 `substr()` 函数可以轻松实现。

```cpp
//s 为这个人的 freopen 语句
//s.substr(a,b) 就是 s 的第 a 至第 b-1 个字符。
if(s.substr(0,10)=="//freopen("&&s.substr(s.length()-2,s.length())==");"){
	flag=1;
}
```

- 乐子人：不需要专门判断，不是上面两类人均为乐子人。

现在每一种的判断方法都介绍完了，那怎么把它们整合到一起呢？

对于每一个人，我们初始标记他是普通人；如果某一个语句满足见祖宗人，则直接标记成见祖宗人，**并跳过这个人后面语句的判断**，**只进行读入**（不读入是不行的，因为后面还有人会导致错乱）；如果某一个语句存在乐子行为，则标记为乐子人，但此时**后面的还要判断**，因为存在见祖宗人的可能。

也就是这样判断每一个人：

```cpp
//flag=0 普通人，1 见祖宗人，2 乐子人
ll flag=0;
for(int i=0;i<2*m;i++){
	cin>>s;
	if(flag==1)continue; //已经是见祖宗人了则不判断
	if(s.substr(0,10)=="//freopen("&&s.substr(s.length()-2,s.length())==");"){//满足见祖宗人
		flag=1;
	}
	else if(i%2==0&&s!=ai[i/2]||i%2==1&&s!=ao[i/2]){//不是见祖宗人且与正常语句不同，满足乐子人
		flag=2;
	}
}
cout<<ans[flag]<<endl; //我用 string 数组存储了输出内容，详见完整代码
```

这样，这个题就愉快地结束啦！

### Part3 注意点及针对部分错误代码的 hack 数据

注意：**只要有 `//freopen();` 就算是见祖宗人**，**即使他有乐子行为**。如果你只过了 subtask2，下面这组 hack 可能救你于水火之中：

```
1
2 1
opop

op
//freopen(");

//freopen();
op
```

可以发现，两个人都存在乐子行为，但其实都是见祖宗人。

### Part4 代码

注释在代码里啦！

```cpp
#include<iostream>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll t,n,m; 
string s,ai[10],ao[10];
//方便输出 
string ans[3]={"PION2202 RP++.","Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.","Good luck and have fun."};
int main(){
	cin>>t>>n>>m;
	for(int i=0;i<m;i++){
		cin>>s;
		//预处理出普通人的语句 
		ai[i]="freopen(\""+s+".in\",\"r\",stdin);";
		ao[i]="freopen(\""+s+".out\",\"w\",stdout);";
	}
	while(n--){
		ll flag=0;//注意清空
		//我这里 flag=0 是普通人，flag=1 是见祖宗人，flag=2 是乐子人 
		for(int i=0;i<2*m;i++){
			cin>>s;
			if(flag==1)continue;//是见祖宗人就不需要再判定了，但是还需要读入，所以写这句
			//使用截取函数 substr 判断见祖宗人 
			if(s.substr(0,10)=="//freopen("&&s.substr(s.length()-2,s.length())==");"){
				flag=1;
			}
			//不是见祖宗人就看是不是普通人 
			else if(i%2==0&&s!=ai[i/2]||i%2==1&&s!=ao[i/2]){
				flag=2;
			}
		}
		cout<<ans[flag]<<endl;//输出 
	}
	return 0;
}
```

---

## 作者：Chtholly_Tree (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8964)

### Part 1 题意

给出每位选手 `freopen` 的代码，判断这位选手是普通人，见祖宗人还是乐子人。

- 普通人：普普通通的 `freopen` 代码。

- 见祖宗人：有至少一句话以 `//freopen(` 开头，以 `);` 结尾。

- 乐子人：其他形式的 `freopen` 语句。

### Part 2 题目解法

那么，本题的优先级为

| 名称 | 优先级 |
| :-: | :-: |
| 见祖宗人 | $3$ |
| 乐子人 | $2$ |
| 普通人 | $1$ |

- 如果这个人同时满足乐子人和见祖宗人的条件，那么他就是见祖宗人。

- 如果这个人同时满足普通人和见祖宗人的条件，那么他就是见祖宗人。

- 如果这个人同时满足普通人和乐子人的条件，那么他就是乐子人。

不妨可以这样：

我们首先定义 $flag$ 变量，用来判断是什么人。（一开始都是普通人，$flag = 1$）

如果这个人的某句 `freopen` 满足见祖宗人的条件，那么将 $flag$ 设为 $3$。

如果这个人的某句 `freopen` 满足乐子人的条件，那么将 $flag$ 设为 $\max(flag, 2)$

或许有人会问，为什么不是把 $flag$ 设为 $2$，而是 $\max(flag, 2)$。

如果把 $flag$ 设为 $2$ 就错了。想一下，如果这个人以前的某句 `freopen` 是见祖宗人的 `freopen`，然后后来又写了一句乐子人的 `freopen`，那么他到底是见祖宗人还是乐子人呢？

没错，答案是见祖宗人。

而且见祖宗人的优先级是 $3$，所以 $\max(flag,2)$ 恰好就可以解决这个问题。

至于怎么判断见祖宗人和乐子人，请见代码。

### Part 3 代码

```cpp
#include <bits/stdc++.h>//头文件不解释
using namespace std;
string name[10], fin[10], fout[10];//定义数组，这里本来大小定义 5 就行，但是我把数组大小定义成了 10
int t, n, m;
int main() {
	ios::sync_with_stdio(0);//优化 1
	cin.tie(0);//优化 2
	cout.tie(0);//优化 3
	cin >> t >> n >> m;//读入数据
	for (int i = 1; i <= m; i++) {
		cin >> name[i];
	}//读入每题的名称
	for (int i = 1; i <= n; i++) {//大循环，枚举每个选手
		for (int j = 1; j <= m; j++) {//因为这里的数组要重复使用，所以每次都要清空
			fin[j] = "";
			fout[j] = "";
		}
		int flag = 1;//Part 2 中的 flag
		for (int j = 1; j <= m; j++) {
			cin >> fin[j] >> fout[j];
		}//读入这个人每次的 freopen
		for (int j = 1; j <= m; j++) {
			string s1 = "", s2 = "";//s1，s2 代表最普通不过的 freopen 格式
			s1 += "freopen(\"" + name[j] + ".in\",\"r\",stdin);";
			s2 += "freopen(\"" + name[j] + ".out\",\"w\",stdout);";
			int lin = fin[j].size(), lout = fout[j].size();//这个人的输入和输出长度，后面有用
			if (fin[j].substr(0, 10) == "//freopen(" && fin[j][lin - 2] == ')' && fin[j][lin - 1] == ';') {
				flag = 3;
			}//fin[j].substr(0, 10)，代表从 fin[j] 这个字符串里截取从第 0 位开始的后 10 位
			if (fout[j].substr(0, 10) == "//freopen(" && fout[j][lout - 2] == ')' && fout[j][lout - 1] == ';') {
				flag = 3;
			}//和上面差不多，判断见祖宗人
			if (fin[j] != s1 || fout[j] != s2) {
				flag = max(flag, 2);
			}//乐子人
		}
		if (flag == 3) {//判断 flag 并输出
			cout << "Wrong file operation takes you to your ancestors along with your 3 years' efforts on OI.\n";
		} else if (flag == 2) {
			cout << "Good luck and have fun.\n";
		} else {
			cout << "PION2202 RP++.\n";
		}
	}
	return 0;//结束
}
```

### Part 4 忠告

十年 OI 一场空，注释 `freopen` 见祖宗。

---

## 作者：OoXiao_QioO (赞：0)



# 前言

只对 SubTask 2 的选手看过来！！！

很好的一道模拟题。

# 坑点分析

题目里说的很明白了：只要有 $\ge 1$ 个带有注释的，就是**一定是**祖宗人，哪怕在后面或者前面出现过符合乐子人的判断。

一组 hack 能简单明了的看出坑点：

```cpp
1
2 1
A

B
//freopen();

//freopen();
B
```

显然答案都是祖宗人。

还需要注意关于换行的问题，如果使用 `scanf()` 和 `getchar()` 就要麻烦的多，但是使用 `cin` 就可以避免这个问题。

弄明白这两个坑点，就可以 AC 了。

# 思路

考虑对每道题生成合法的 `.in` 与 `.out` 的 `freopen()`，与输入的进行比较，如果**完全一致**，就是普通人，如果前面有 `//freopen	` 且后面有 `);`，就**一定**是祖宗人，其余情况就是乐子人。

思路是很清晰的，主要是细节问题，在代码里会讲解。

如何生成符合标准的 `freopen()` 呢？看到只有题目名字不一样，我们就可以用 `string` 拼接出一个合法的语句。

但是 `.in` 和 `.out` 以及 `stdin` 和 `stdout` 也存在差异，只需要判断行数是否是偶数就可以了。

这一部分的代码：

```cpp
for(i=1;i<=2*m;i++)
{
	string k = (i%2==1)?".in\",":".out\","; //这是关于后缀名的处理。
	string k1 = (i%2==1)?"\"r\",stdin);":"\"w\",stdout);";//这是关于是读入还是输出的处理。
	tque[i] = "freopen(\""+que[(i+1)/2]+k+k1;//这是存储合法的语句的数组。
}
 ```
关于双引号的细节很多，读者一定要看明白。

现在就开始特判是哪种人了，再次重申：只要有**一个**符合祖宗人的标准，哪怕同时符合了乐子人的标准，答案还是祖宗人。

对于这一个判断，需要开一个变量 `zzr`（是否是祖宗人），只要满足祖宗人的标准，就设为 $1$，以后如果出现了乐子人，就不管他了。

关于这一部分的代码：

```cpp
getchar();//把可恶的换行吃掉。 
string s;//每一行输入的东西。 
int f = 0;//0:RP++,1:Wrong,2:Good。 
int zzr;//祖宗人标志。 
for(i=1;i<=n;i++)//遍历选手。 
{
	f = 0;
	zzr = 0;//初始为 0。 
	for(j=1;j<=2*m;j++)//遍历输入。 
	{
		int l;
		cin>>s;
		l = s.size();
		if(zzr)//只要出现了祖宗人，答案一定是祖宗人，跳过就可以了。 
			continue;
		if(s[0]=='/'&&s[1]=='/'&&s[2]=='f'&&s[l-1]==';'&&s[l-2]==')')//判断是否是祖宗人。 
		{
			f = 1;
			zzr = 1;
			continue;
		}
		else if(s==tque[j])//普通人。 
			;
		else//不是普通人且不是祖宗人，就是乐子人。 
		{
			f = 2;
			continue;
		}
	}
	if(f==0)//判断输出。 
		puts("PION2202 RP++.");
	else if(f==1)
		puts("Wrong file operation takes you to your ancestors along with your 3 years\' efforts on OI.");
	else
		puts("Good luck and have fun.");
}
```

对于完整程序，把两部分拼起来，并加上输入定义等部分就可以了，不予展示。



---

