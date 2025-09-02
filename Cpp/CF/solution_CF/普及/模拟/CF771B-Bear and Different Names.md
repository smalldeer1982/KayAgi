# Bear and Different Names

## 题目描述

In the army, it isn't easy to form a group of soldiers that will be effective on the battlefield. The communication is crucial and thus no two soldiers should share a name (what would happen if they got an order that Bob is a scouter, if there are two Bobs?).

A group of soldiers is effective if and only if their names are different. For example, a group (John, Bob, Limak) would be effective, while groups (Gary, Bob, Gary) and (Alice, Alice) wouldn't.

You are a spy in the enemy's camp. You noticed $ n $ soldiers standing in a row, numbered $ 1 $ through $ n $ . The general wants to choose a group of $ k $ consecutive soldiers. For every $ k $ consecutive soldiers, the general wrote down whether they would be an effective group or not.

You managed to steal the general's notes, with $ n-k+1 $ strings $ s_{1},s_{2},...,s_{n-k+1} $ , each either "YES" or "NO".

- The string $ s_{1} $ describes a group of soldiers $ 1 $ through $ k $ ("YES" if the group is effective, and "NO" otherwise).
- The string $ s_{2} $ describes a group of soldiers $ 2 $ through $ k+1 $ .
- And so on, till the string $ s_{n-k+1} $ that describes a group of soldiers $ n-k+1 $ through $ n $ .

Your task is to find possible names of $ n $ soldiers. Names should match the stolen notes. Each name should be a string that consists of between $ 1 $ and $ 10 $ English letters, inclusive. The first letter should be uppercase, and all other letters should be lowercase. Names don't have to be existing names — it's allowed to print "Xyzzzdj" or "T" for example.

Find and print any solution. It can be proved that there always exists at least one solution.

## 说明/提示

In the first sample, there are $ 8 $ soldiers. For every $ 3 $ consecutive ones we know whether they would be an effective group. Let's analyze the provided sample output:

- First three soldiers (i.e. Adam, Bob, Bob) wouldn't be an effective group because there are two Bobs. Indeed, the string $ s_{1} $ is "NO".
- Soldiers $ 2 $ through $ 4 $ (Bob, Bob, Cpqepqwer) wouldn't be effective either, and the string $ s_{2} $ is "NO".
- Soldiers $ 3 $ through $ 5 $ (Bob, Cpqepqwer, Limak) would be effective, and the string $ s_{3} $ is "YES".
- ...,
- Soldiers $ 6 $ through $ 8 $ (Adam, Bob, Adam) wouldn't be effective, and the string $ s_{6} $ is "NO".

## 样例 #1

### 输入

```
8 3
NO NO YES YES YES NO
```

### 输出

```
Adam Bob Bob Cpqepqwer Limak Adam Bob Adam```

## 样例 #2

### 输入

```
9 8
YES NO
```

### 输出

```
R Q Ccccccccc Ccocc Ccc So Strong Samples Ccc```

## 样例 #3

### 输入

```
3 2
NO NO
```

### 输出

```
Na Na Na```

# 题解

## 作者：zhouchuer (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF771B)
## 思路
这题还是很简单的，讲一下思路。

先输入 $n$ 和 $k$，然后输入 $n-k+1$ 个要求。

我们先假设输入的要求全都是 YES，那也就是说每个名字都不同，我们先写一个随机生成名字的循环嵌套，存在一个字符串数组 $s$ 中。

然后才是这题的关键，如果输入 NO 就表示从第 $i$ 个名字到第 $i+k-1$ 个名字这个区间里至少有两个相同名字，所以让区间首尾元素为同一个名字即可。

名字生成也讲一下，就用一个大写字母加上几个小写字母就行了，可以用循环，建议 $s_i$ 的长度在一至十个字符之间，我觉得三个应该够了。
## 样例解释
解释一下第二组吧。

样例输入：
```c
9 8
YES NO
```

然后是样例输出：
```c
R Q Ccccccccc Ccocc Ccc So Strong Samples Ccc
```

首先输入 $n$ 和 $k$，分别是 $9$ 和 $8$，然后从第 $1$ 个名字到第 $8$ 个名字都不相同，第 $2$ 到第 $9$ 个名字中至少有两个相同名字，所以保证区间里有两个相同名字即可。

输入 YES 就不用说了吧，直接跳过即可。
```c
if(sr=="YES") continue;//sr只是为了方便理解
```

生成完之后如果输入遇到 NO，就用下面这个关键的一句代码就行了：
```c
if(sr=="NO") s[i+k-1]=s[i]; //sr只是为了方便理解
```

都看到这里了，赶紧去写代码吧！

---

## 作者：Pyrf_uqcat (赞：2)

## 题意
一共有 $n$ 个名字，要满足 $n-k+1$ 个要求（YES：从第 $i$ 个到第 $i+k-1$ 个名字各不相同；NO：从第 $i$ 个到第 $i+k-1$ 个名字至少有两个相同）。


------------

## 思路
难点主要在于应该怎么满足条件。

思考：在输入过程中，如果第 $i$ 个要求为 NO 那么哪一项应该与第 $i$ 项相同。

假设第 $i-1$ 个要求为 YES，第 $i-1$ 个要求是从第 $i-1$ 项判断到第 $i+k-2$ 项，而第 $i$ 个要求则是从第 $i$ 项判断到第 $i+k-1$ 项，关键点在于第 $i-1$ 个要求的 YES 判断不到第 $i+k-1$ 项，所以只有第 $i+k-1$ 项才能与第 $i$ 项相同。

因此在输入过程中，遇到 NO 时将第 $i$ 项的名字赋值给第 $i+k-1$ 项就可以了，而在遇到 YES 时直接跳过。

输入核心代码
```cpp
for(int i=1;i<=(n+k-1);i++) {
		string s;
		cin>>s;
		if(s=="YES") continue;
		else name[i+k-1]=name[i];
        //变量名name只是举个例子，便于理解
	}
```

---

## 作者：封禁用户 (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf771b-bear-and-different-names-de-ti-jie/)
## 思路
首先假设所有的名字都是不一样的，所以在遇到 $\texttt{Yes}$ 的时候就不需要进行处理。

当遇到 $\texttt{No}$ 的时候，可以直接假设 $name_{i+k-1}=name_{i}$。这样假设有一个好处，因为当在访问 $name_{i+1}$ 的时候，$name_i$ 就不会被考虑了，所以即使是 $\texttt{Yes}$ 也不会影响。

**注意**：翻译并没有翻译出名字的长度 $len$，应该满足 $len\in[1,10]$。
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100;
int n,k;
char c[N];
vector<char> ans[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		ans[i].push_back(i%26+'A');
		ans[i].push_back((i+i/26)%26+'a');
	}
	for(int i=1;i<=n-k+1;i++){
		cin>>c;
		if(c[0]=='N') ans[i+k-1]=ans[i];
	}
	for(int i=1;i<=n;i++){
		for(char j:ans[i]){
			cout<<j;
		}
		cout<<' ';
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 思路

乍一看没啥思路，但是我们可以考虑最坏情况。

假设 $i-1$ 和 $i+1$ 都是 ```YES``` 而 $i$ 是 ```NO```。这个时候怎么办呢？我们发现只需要把 $i$ 和 $i+k-1$ 这两个位置设置成相同的就可以了。这种方法只对 $i$ 有影响，是无后效性的。所以最后的思路就是，对于 $1$ 到 $n$ 每个位置 $i$ 先放上一个数 $i$，然后判断所有的 ```YES```，将 $i$ 赋值给 $i+k-1$。最后对于每个不同的数，我们直接随便输出一个不同的单词即可。这样做不仅效率高的一匹，而且容易实现。

但是作为萌新，我不会随机输出怎么办？

其实很简单。只需要对于每个单词，把它转化成 ```a~z``` 的 26 进制即可。注意首字母大写 qwq！

## 代码

可能是整数的常数小，跑得飞快，不开 O2 不卡常坐稳最优解！

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
string turn(int x)
{
	string s="";
	while(x) s+=(char)(x%26+'a'),x/=26; // 整数转化成 26 进制
	s[0]=s[0]-'a'+'A'; //首字母大写
	return s;
}
int main()
{
	int n,k; cin>>n>>k;
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=n-k+1;i++)
	{
		string x; cin>>x;
		if(x=="YES") continue;
		a[i+k-1]=a[i]; // 处理 'NO' 的情况
	}
	for(int i=1;i<=n;i++)
		cout<<turn(a[i])<<" "; // 把数字转化成字符输出
	return 0;
}
```

---

## 作者：__qkj__ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF771B)

这一题是一道构造题，先把他们的名字初始化，因为字符串比较难控制，所以就用整型构造，最后再转换为字符串。

先把数组初始化成不同的整数，再输入 $n-m+1$ 个字符串，遇到 `YES` 直接跳过（因为数组本来就是两两不同的），当输入 `NO` 时，把第 $i+m-1$ 项和第 $i$ 项置成一样，就能达到题目的要求。

最后就是把整数转化成字符串了。先输出一个 `A`（第一个得是大写），再把整数每一项加上一个字符 `a`，就可以输出了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[60];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)a[i]=i; //初始化
    for(int i=1;i<=n-m+1;i++)
    {
        string s;
        cin>>s;
        if(s=="NO")a[i+m-1]=a[i]; //置成一样
    }
    for(int i=1;i<=n;i++)
    {
        cout<<'A'; //首字母大写
        int t=a[i];
        while(t)  //转字符串
        {
            cout<<char(t%10+'a');
            t/=10;
        }
        cout<<' ';
    }
    return 0;
}
```

---

## 作者：flowerfell_sf (赞：0)

整体思路为去构造。
***
首先把 $ n $ 个名字置成不同的整数（字符串比较难），然后输入 $ n - k + 1 $ 个 `YES` 或 `NO`，如果输入的是 `NO`，把 $ a_{i+k-1} = a_i $，使第 $ i $ 个名字和第 $ i+k−1 $ 个名字有两个相同的名字。

最后输出数组，因为名字开头是大写，所以先输出 `A`。再输出每个数字加 `a`。

***
附上本辣鸡的拙作

```cpp
#include<bits/stdc++.h>
#define For(i,x,y) for(int i=x;i<=y;i++)
#define Dor(i,x,y) for(int i=x;i>=y;i--)
typedef long long ll;//本辣鸡做题习惯
using namespace std;
int x[60],n,m;//这里的x数组为上文的a
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);//这里也是
    cin>>n>>m;
    For(i,1,n)x[i]=i;
    For(i,1,n-m+1)
    {
        string s;
        cin>>s;
        if(s=="NO")x[i+m-1]=x[i];//把x的i-m+1项赋值a的第i项
    }
    For(i,1,n)
    {
        cout<<'A';
        int t=x[i];
        while(t)
        {
            cout<<char(t%10+'x');//将t按位转化为字符输出
            t/=10;
        }
        cout<<" ";
    }
    return 0;
}
```
***
码风不是很好，请见谅

---

## 作者：qusia_MC (赞：0)

番外 & 警示：

不能是最后两个相同！！因为：（前提是 $k \ge 3$）若是两个是 `NO` 和 `YES` 连起来的话，照样的话，设前面的名字是 "Aa"，则后面 "NO" 就会将这个名字也设为 "Aa"，再一个 "YES"，前面的两个 "Aa" 就会不符合要求。所以给大家警示，别想得那么简单！
## 分析
就是给你 $n - k + 1$ 个 `YES` 或 `NO` 让你构造 $n$ 个名字，满足要求即可。具体题目说了，这里不再重申。

## 思路

看一眼数据，嘿！$n\le 50$，这不就舒服了！看这题代码难度肯定不大，要的就是思路。

构造，肯定要的就是最优构造。肯定就是让 `NO` 的时候就两个一样的名字。

于是呢，我们可以存储好当前构造的名字的前 $k-1$ 个名字存储下来，每次给你的一个信息（这里和以后都指代 `YES` 或 `NO`）都扫一遍：

- 如果已经有两个相同的就啥事不用干，就输出下一个名字。

- 没有，且信息是 `NO` 的话，我们要求最优构造，则这个要和存储的 $k-1$ 个之前的名字的第 $1$ 个一样就 OK 了（别问我为啥不用最后一个，开头就是例子）。

最后插一嘴在处理的时候最好用 `vector<string>` 或队列。动态调整，每输出一个就把输出的存到最后面（`push_back` 或 `push`）。

## 代码
为啥好多题解都不写代码，多简单啊。。
```
#include <bits/stdc++.h>
using namespace std;
string name[53] = {"Cee", "Aaa", "Abb", "Acc", "Add", "Aee", "Aff", "Ags", "Aha", "Aif", "Ajs", "Akf", "Ajl", "Adm"
, "Aggn", "Afgmo", "Apsfgfs", "Aqsdfg", "Arsdfg", "Asfdgs", "Adfgt", "Auasdfv", "Avbfdh", "Awadsgv", "Axagdv", "Aadfgy", "Aagbdz", "Baagdsb",
"Bbsd", "Bvncxc", "Bczbd", "Bvxe", "Bncbf", "Bmg", "Bzxc", "Biascf", "Bjadfv", "Bkfadhb", "Blgdabdhg", "Bgsadbm", "Badsgbn", "Basdgbo",
"Bpgsd", "Bqsfdhs", "Bsfdhr", "Bsrss", "Bdgert", "Buegsrt", "Byfdzv", "Bwfdvfsdh", "Brgsfhsx", "Bfysdfy", "Bsdfgsz"}, s[51];
//手敲名字（键盘：我谢谢你）
int n, k;
vector <string> v;//也可以用 queue
int main ()
{
	cin >> n >> k;
	for (int i = 1; i <= n - k + 1; i ++)
		cin >> s[i];
	for (int i = 1; i < k; i ++)
	{
		cout << name [i] << " ";//开始就输出不一样的就OK
		v.push_back(name[i]);
	}
	int j = k - 1;
	for (int i = 1; i <= n - k + 1; i ++)
	{
		bool f = 1;
		for (int i = 1; i < k - 1; i ++)
				if (v[i] == v[i - 1])
				    f = 0;//前面有没有一样的？？
		if (k == 2) f = 1;
		if (s[i] == "NO" && f)
		{
			cout << v[0] << " ";
			v.push_back(v[0]);// k-1 个名字
			v.erase (v.begin());
		}
		else {
			cout << name[++ j] << " ";
			v.push_back(name[j]);
			v.erase (v.begin());//下一个
		}
    }
    return 0;
}
```

---

## 作者：Trimsteanima (赞：0)

### Description
$n$个名字需要满足$n-k+1$个要求，每个要求只有`YES`或`NO`，如果第$i$要求是`YES`则第$i$个名字到第$i+k-1$个名字都不相同，如果第$i$个要求是`NO`则第$i$个名字到第$i+k-1$个名字至少有两个相同，要输出其中一种满足所有要求的方案。

### Solution
首先先不考虑要求生成$n$个名字，考虑一下如果第$i$个要求为`NO`，则使第$i$个名字和第$i + k-1$个名字相等。也就是不需要考虑`YES`的要求。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200;
string s[N], s1;
int n, k;
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        s[i] = "Aa", s[i][0] += i / 26, s[i][1] += i % 26;
    for (int i = 1; i <= n - k + 1; i++) {
        cin >> s1;
        if (s1[0] == 'N') s[i + k - 1] = s[i];
    }
    for (int i = 1; i <= n; i++) cout << s[i] << ' ';
    printf("\n");
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF771B)
### 题目思路：
其实这一道题就是简单的构造。首先，我们看到如果说全都是 $YES$ 的情况，那么所有的名字都是不同的，所以我们只要先初始化数组中所有的下标 $i$，保证每个名字不同。然后开始输入字符串，当字符串为 $NO$ 时，我们就按题目意思把第 $i+k-1$ 项赋值为和当前位相同的，保证第 $i$ 个名字到第 $i+k-1$ 个名字之间至少有两个相同的名字。最后，我们把每个名字输出，因为我们数组中的元素都是整型，所以我们把数字转换为对应的字符串，别忘了首字母大写哦。代码这里就不贴了，大家自己想一想吧。

---

## 作者：SJH__qwq (赞：0)

简单题。

考虑设 $a_i$ 表示 $i$ 用了第 $a_i$ 个名字。其中名字可以随机生成。

然后若出现 `YES` 则表示 $i-k+1\sim i$ 中至少有一对名字相同。那么钦定 $a_i=a_{i-k+1}$ 即可满足题目中的条件。

最后直接根据钦定的名字输出即可。时间复杂度 $O(n)$。

---

## 作者：lgydkkyd (赞：0)

分析完题目，乍一看是一道构造题，其实浅浅写个构造就行了。每次输入一个字符串为 YES 或者是 NO ，如果是 YES 就不用管，直接跳过，重点是 NO 的这种情况，就可以将第 $i+k-1$ 赋值为第 $i$ 项，在此之前还要初始化答案数组，下标为 $i$ 的赋值为 $i$ 就好了，最后再输出我们的答案数组便可以拿下这道题目了，完结撒花！这里就不放代码了，考验大家的思维能力。

---

## 作者：tallnut (赞：0)

# 思路
## 整型构造
我们可以先构造整型，之后再转为字符串输出。

先往答案数组 $ans$ 中填入 $n$ 个不同的数。然后对每一条限制条件做判断：如果为 `YES` 的话就可以直接忽略，因为答案数组的每个元素初始值就各不相同。否则就要进行修改，可以
$$ans_{i+k-1} \gets ans_{i}$$
这样就可以保证在 $[i,i+k-1]$ 这一区间里至少有两个元素相同。
## 转换为字符串
直接把整型当作 $26$ 进制数，就可以转换为全部是小写的 $26$ 进制数。不过题目要求“首字母大写，其余小写”，因此我在实现中提前输出了一个 `A`（当然其他大写字母也可以），保证开头是大写。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/138541980)，代码中有注释。
```
#include <iostream>
using namespace std;
int n,k;
string tmps;
int ans[51];
//把整形转成字符串输出
void output_int_as_str(int x)
{
	//这一行是为了保证名字开头为大写
	putchar('A');
	while (x)
	{
		putchar('a' + x % 26);
		x /= 26;
	}
	putchar(' ');
}
int main()
{
	cin >> n >> k;
	for (int i = 1;i <= n;i++)
		ans[i] = i;
	for (int i = 1;i <= n - k + 1;i++)
	{
		cin >> tmps;
		//贪心地修改
		if (tmps == "NO") ans[i + k - 1] = ans[i];
	}
	for (int i = 1;i <= n;i++)
		output_int_as_str(ans[i]);
}
```

---

