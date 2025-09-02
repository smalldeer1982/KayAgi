# One-dimensional Japanese Crossword

## 题目描述

最近，阿德蒂克发现了日语填字游戏。日语填字游戏是一幅图片，表示为一张桌子大小的a×b正方形，每个方格都是白色或黑色的。
行的左边和列的顶部都有整数，对相应的行或列进行加密。整数的数量表示对应的行或列中有多少组黑色方块，整数本身表示相应组中连续的黑色方块的数量(您可以在维基百科[https://en.wikipedia.org/wiki/Japanese_crossword](https://en.wikipedia.org/wiki/Japanese_crossword)）_纵横字谜中找到更详细的解释)。

阿德蒂克认为日语填字的一般情况太复杂，画了n个正方形(例如1×n1×n)的一行，他想用和日语填字一样的方式加密。

对一行日文横线进行加密的例子。帮助阿德蒂克找到对他画的行进行加密的数字。

## 样例 #1

### 输入

```
3
BBW
```

### 输出

```
1
2 ```

## 样例 #2

### 输入

```
5
BWBWB
```

### 输出

```
3
1 1 1 ```

## 样例 #3

### 输入

```
4
WWWW
```

### 输出

```
0
```

## 样例 #4

### 输入

```
4
BBBB
```

### 输出

```
1
4 ```

## 样例 #5

### 输入

```
13
WBBBBWWBWBBBW
```

### 输出

```
3
4 1 3 ```

# 题解

## 作者：wuwenjiong (赞：2)

温馨提示：别看题目~~好像很难懂~~，实际上十分简单。
## 题意：
一个只由 $B$ 和 $W$ 构成字符串， $B$ 代表黑格子， $W$ 代表白格子。求只由 $B$ 构成的子串的个数，并输出每个子串一共有多少个 $B$ 。
### 样例5分析：
样例输入：
```cpp
13
WBBBBWWBWBBBW
```
样例输出：
```cpp
3
4 1 3 
```
第一个是 $W$ ，不管它，第二个就是 $B$ 了，开始计算， $k$ 加一，后来连续 $4$ 个 $B$ ，第六个字符是 $W$ ，此时 $k=4$ ，那么就将 $k$ 的值存入数组，并且子串个数 $s$ 加一。其他的可以直接看出，一共有 $3$ 段 $B$ 的子串，且子串长度分别为 $4,1,3$ 。所以输出：
```cpp
3
4 1 3 
```
更具体的**解析**见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[105],i,n,k=0,s=0;
	char c[105];
	cin>>n>>c;//可以不用for循环读入字符串
	for(i=0;i<n;i++)//for循环查找
	{
		if(c[i]=='B')
			s++;//记录B连续出现的次数
		else if(s!=0)//这个一定要判断，防止出现连续的'W'
		{
			k++;//当一个B的子串结束后，子串数加一。
			a[k]=s;//用数租将个数存起来，便于后面输出
			s=0;//记得把s归零
		}
	}
	if(s!=0)//特判最后不是以'W'结尾的情况
	{
		k++;
		a[k]=s;
	}
	cout<<k<<endl;//输出子串的个数
	for(i=1;i<=k;i++)
		cout<<a[i]<<' ';//for循环依次输出每段B子串的长度
	return 0;
}
```
谢谢！！！

---

## 作者：Cambridge (赞：1)


蒟蒻又来发题解了！

### 思路

对题意进行归纳，其实就是给你一个字符串，让你求出其中只包含字母 B 的连续性子串有几个，并输出子串长度。

知道题意后，这道题就不难了。我们在读入字符串后，每一位逐一枚举，如果当前位置是字母 B ，那我们就一个 while 循环求出这一只包含字母 B 的连续性子串，在遇到字母 W 后退出 while 循环，然后用 a 数组储存该子串，子串个数加1，最后输出即可。

思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<vector>
#include<fstream>
#include<algorithm>//文件头不解释
using namespace std;
int n,gs,ans,a[1000000];
string st;//定义变量
int main()
{
    cin>>n>>st;//读入字符串长度和字符串
    for(int i=0; i<n; i++)
    {
    	while(st[i]=='B')gs++,i++;//求子串
    	if(gs)a[++ans]=gs,gs=0;//如果遇到了W即退出了while循环，记录子串
	}
	if(gs)a[++ans]=gs,gs=0;//本蒟蒻为了以防万一，虽然貌似可有可无
	cout<<ans<<endl;//输出子串个数
	for(int i=1; i<=ans; i++)
		cout<<a[i]<<' ';//输出每个字串长度
    return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：xukuan (赞：1)

## 翻译：

#### 题目描述：

这是一个日本一维填字游戏的简化版。

给定一个包含n个字符的字符串，仅由'B'和'W'两种字符构成。

请计算字符串中有几段仅由'B'构成的子串，每段的长度依次是多少。

例如：长度为13的字符串"WBBBBWWBWBBBW"，共有3段"B"串，长度依次为4,1,3。

#### 样例输入：

第一行，一个整数n(1≤n≤100)，表示字符串的长度；

第二行，一个仅由'B'和'W'两种字符构成的字符串。

#### 样例输出:

第一行，一个整数，表示"B"串的数量。

第二行，依次输出每段"B"串的长度。

## 题解：

这种题没什么可说的，直接无脑模拟即可（毕竟这是红题）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n,a[110],tot;
string s;

int main(){
	cin>>n;
	cin>>s;
	for(ll i=0; i<n; i++){
		if(s[i]=='B'&&(s[i-1]!='B'||i==0)) a[++tot]=1;
		else if(s[i]=='B'&&s[i-1]=='B'&&i!=0) a[tot]++;
	}
	printf("%lld\n",tot);
	for(ll i=1; i<=tot; i++) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：luqyou (赞：0)

# 题意

给你一个串黑白格（输入样例中用“B”和“W”表示黑和白），问你连续黑串的个数以及黑串的长度。

# 思路

我们用一个变量 $ ans $ 来记录连通块的数量，用数组 $ an $ 来记录每个黑串的长度，同时一个数组指针 $ n $ 来告诉 $ an $ 长度应该填哪里，即遇到黑串后的第一个白块就 $ +1 $.

同时一个注意点，如果字符串末尾为白格，是不会计入总数的！

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001];
int ans,an[1001],n=1;
bool liantong=0;
int main(){
	int len;
	cin>>len>>a;
	for(int i=0;i<len;i++){
		if(a[i]=='B'){
			liantong=1;
			an[n]++;
		}
		else{
			if(liantong){
				n++;
			}	
			liantong=0;
		}
	}
	if(a[len-1]!='B') n--;//特判
	cout<<n<<endl;
	for(int i=1;i<=n;i++){
		cout<<an[i]<<" ";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

一道字符串模拟题

题目描述可能看不懂,其实题意很简单:找出字符串中由B组成子串的个数,并输出每个子串的长度即可

思路:用数组 $a$ 存储各子串长度, $cnt$ 存储子串个数

$Code:$
```
#include<bits/stdc++.h>
using namespace std;
int main (){
	int n,a[109]={0},cnt=0;//a数组储存每个子串的长度,cnt为子串数量
	string s;//利用c++的string功能即可
	cin>>n>>s;//输入(其实n没什么用)
	for (int i=0;i<n;i++){//注意字符串是从s[0]开始输入的
		if (s[i]=='B'&&(s[i-1]!='B'||i==0)){
        //若该字符为B且(上一个字符不是B或者i=0)
        //注意逻辑关系,c++中且的优先级更高,所以要打括号
        //这种情况相当于由B组成的子串数量多了一个
			cnt++;//数量增加一个
			a[cnt]++;//这个子串的长度+1
        //其实也可以写成a[cnt]=1,因为之前这个元素一定是0
		}
		if (s[i]=='B'&&s[i-1]=='B'&&i!=0)
        //如果上一个和这个字符都是B
        //这里没有产生新的符合题意的子串
		a[cnt]++;
        //只要给该子串长度+1即可
	}
	cout<<cnt<<endl;//输出个数
	for (int i=1;i<=cnt;i++)//一定要从1开始循环
	cout<<a[i]<<" ";//输出,记得加空格
	cout<<endl;
	return 0;
}
```

谢谢阅读!

---

## 作者：happybob (赞：0)

~~发现我的评测是最快的！465ms~~

题目看得迷迷糊糊，看了样例就懂了，原本是想把答案存到数组，突然想起了 `stringstream`，直接把答案放在那里最后输出呗！

然后我又想，第一个读入不是没有用吗？为啥不用 `scanf(%*d);` 把它吞了呢？

但是碰到这种题目有一点要考虑！如果一直是 `B`，那循环完根本没有统计过，所以我们在读入的字符串后面加一个 `W`，这样就可以在最后再统计一遍啦！

代码：

```cpp
#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
using namespace std;

int main()
{
	stringstream ans;
	string s;
	scanf("%*d");
	cin >> s;
	s.push_back('W'); // 最好用自带函数，不然可能会RE
	int len = s.length() - 1, cnt = 0, now_black = 0;
	for (register int i = 0; i <= len; i++)
	{
		if (s[i] == 'B') now_black++;
		else
		{
			if (now_black == 0) continue;
			cnt++;
			ans << now_black;
			ans << " ";
			now_black = 0;
		}
	}
	ans << '\n';
	cout << cnt << endl << ans.str();
	system("pause");
	return 0;
}
```


---

## 作者：sodak (赞：0)

## 思路
这道题好像就题目有一点难理解，大概就是求每一个连续B段的长度，模拟一下就可以了

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register 
#define gc getchar()
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
int sta[101],top;
int main(){
	int n=read();
	int cnt=0;
	while(n--){
		char ch=gc;
		if(ch=='B')cnt++;
		else if(cnt)sta[++top]=cnt,cnt=0;
	}
	if(cnt)sta[++top]=cnt;
	printf("%d\n",top);
	for(int i=1;i<=top;i++)printf("%d ",sta[i]);
}

```

---

## 作者：LiteratureCollege (赞：0)

这题的题意很难理解，但是只要知道了题意所求之后便很好写了；

一句话题意：求一个长度为N的字符串中连续的B串个数及其长度。

那么我们可以直接模拟，当扫到一个B时，答案加以利一，然后不停循环到W为止，然后在长度数组中记下这个答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,zjy,a[100416],gy,t;
string s;
int main()
{
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='B')//如果检测到了一个B 
		{
			zjy++;//答案+1 
			int t=0;
			while(s[i]=='B')//一直没有检测到W 
			{
				t++;//长度+1 
				i++;//往后移一位 
			}
			a[++gy]=t;//记入长度数组 
		}
	}
	cout<<zjy<<"\n";
	for(int i=1;i<=gy;i++)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}
/*
zjy
*/
```


---

## 作者：_xyz_hh (赞：0)

题目的大概意思是让你求出```B```串的个数，以及每一个的长度len，然后输出就好了。

~~无 脑 模 拟~~

```cpp
#include <iostream>//标准头文件
#include <cstring>//string专用头文件
#define ll long long//宏定义
using namespace std;//命名空间
const int N = 1e6 + 5;//定义数组大小
ll n, a[N], tot = 0;//定义题目需要的变量，ll就是long long
string str;//方格所需字符串
int main() {//主函数
	cin >> n;//输入方阵长度
	cin >> str;//输入方阵
	for (ll i=0; i<n; i++){//循环判断
		if (str[i] == 'B' && (str[i - 1] != 'B' || i == 0)) {//如果现在是B，而前面不是B
        	a[++tot] = 1;//就是一个新B串
        }
		else if (str[i] == 'B' && str[i - 1] == 'B' && i != 0) {//如果是B，且前一个是B
			a[tot]++;//则当前B串长度加1
		}
	}
	printf("%lld\n", tot);//输出一共有几个B串
	for (ll i=1; i<=tot; i++) {//循环
		printf("%lld ", a[i]);//输出每个B串的长度
	}
	return 0;//华丽结束❀
}
```

~~无耻求赞~~

管理大大求过QWQ

---

## 作者：HarryCecil (赞：0)

谔谔，童鞋们，这题可是**红题**啊！

题目的大概意思，就是让你求出```B```串的个数，以及每一个的长度。

那不是很简单吗，直接无脑模拟即可。

上代码：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
string s;//字符串 
long long n,a[101],t;//定义 
int main(){
    cin>>n>>s;//读入 
    for(long long i=0;i<n;i++){
        if(s[i]=='B'&&s[i-1]=='B'&&i) a[t]++;//如果是B，且前一个是B，则当前B串长度加1 
        else if(s[i]=='B'&&(s[i-1]!='B'||i==0)) a[++t]=1;//如果现在是B，而前面不是B，就是一个新B串 
    }
    cout<<t<<endl;//输出一共B串有几个 
    for(long long i=1;i<=t;i++) cout<<a[i]<<" ";//输出每个B串的长度 
    return 0;
}
```

无耻求赞~

---

## 作者：TianLuen (赞：0)

# CF721A C++题解
### 题目描述
- 有一个长度为 $n$ 的字符串 $a$ 。
- $a_i$ 的值可能是白色，也就是 'W' ，可能是黑色，也就是 'B' 。
- 求的是连续的黑色块的长度和每一段的长度
### 题目分析
看完题目后，可以得知这是一道比较基础的模拟题。

方法是逐一比对 $a_i$ 和 $a_{i-1}$ ，然后按照要求存储好，最后输出。

如何存储？因为只要求黑色的长度，所以在每次读到白色时存储即可。

具体操作，请看代码 ↓
### 代码
```cpp
#include<iostream>
using namespace std;
char a[101];
int n,t,add,ans[100];
	//我变量比较喜欢开全局变量，因为可以初始化为0
int main()
{
    cin>>n;
    cin>>a;
    	//上面是输入
    for(int i=0;i<n;i++)
    {
        if(a[i]=='B')
            t++;	//每次读到黑色时，计数器+1
        else
        {
            if(t>0)
            {
                ans[add]=t;
                add++;
            }
            t=0;	//否则进行存储，存储到ans数组中，这里我用了一个指针add
        }
    }
    if(t>0)
    {
        ans[add]=t;
        add++;
    }	//这时还需要处理一次，容易忘记导致WA
    	//最后输出
    cout<<add<<endl;
    for(int i=0;i<add;i++)
        cout<<ans[i]<<" ";
    return 0;
}
```


---

## 作者：不到前10不改名 (赞：0)

//其实也可以不用数组存，一道模拟水题~QAQ
```
#include<stdio.h>
int main()
{
    int n,srx[101],sry=0,i;//从0开始记录
    char t,q;//两个字符解决问题
    scanf("%d\n",&n);
    for(i=1;i<=n;++i)
    {scanf("%c",&t);
    if(t=='B'&&q!=t)//初次出现
    {++sry;//增加段数
    srx[sry]=1;}//更新为1（其实也可以偷懒直接清为1）
    else if(t=='B'&&q==t)//已经出现过 
    srx[sry]++;//增加连续出现次数
    q=t;}//记录上一个字符
    printf("%d\n",sry);//总段数
    for(i=1;i<=sry;++i) 
    printf("%d ",srx[i]);//每次出现次数
    return 0;
}
```

---

