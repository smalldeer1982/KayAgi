# New Year and North Pole

## 题目描述

In this problem we assume the Earth to be a completely round ball and its surface a perfect sphere. The length of the equator and any meridian is considered to be exactly $ 40000 $ kilometers. Thus, travelling from North Pole to South Pole or vice versa takes exactly $ 20000 $ kilometers.

Limak, a polar bear, lives on the North Pole. Close to the New Year, he helps somebody with delivering packages all around the world. Instead of coordinates of places to visit, Limak got a description how he should move, assuming that he starts from the North Pole. The description consists of $ n $ parts. In the $ i $ -th part of his journey, Limak should move $ t_{i} $ kilometers in the direction represented by a string $ dir_{i} $ that is one of: "North", "South", "West", "East".

Limak isn’t sure whether the description is valid. You must help him to check the following conditions:

- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the North Pole, he can move only to the South.
- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the South Pole, he can move only to the North.
- The journey must end on the North Pole.

Check if the above conditions are satisfied and print "YES" or "NO" on a single line.

## 说明/提示

Drawings below show how Limak's journey would look like in first two samples. In the second sample the answer is "NO" because he doesn't end on the North Pole.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750B/9bb594fe352848bbba36035935a49c02ad65109a.png)

## 样例 #1

### 输入

```
5
7500 South
10000 East
3500 North
4444 West
4000 North
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
15000 South
4000 East
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
20000 South
1000 North
1000000 West
9000 North
10000 North
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3
20000 South
10 East
20000 North
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
2
1000 North
1000 South
```

### 输出

```
NO
```

## 样例 #6

### 输入

```
4
50 South
50 North
15000 South
15000 North
```

### 输出

```
YES
```

# 题解

## 作者：Hanghang (赞：2)

# 又是一道大水题目

## [题目传送门](https://www.luogu.com.cn/problem/CF750B)

## [AC记录](https://www.luogu.com.cn/record/44895052)

### 简单分析一下，发现本题目其实跟向东西走没有关系

### 那就好办了，直接开个变量存纬度

话不多说，直接上代码（带了注释很好理解哦）

```cpp

#include<bits/stdc++.h>
using namespace std;
//还是那句话，万能头大法好

int n,s;
//n表示有多少个部分组成，s表示当前纬度
int main()
{
	cin>>n;
   //正常读入
	for(int i=1;i<=n;i++)
   //循环n次，
	{
		int x;string y;cin>>x>>y;
      //x表示当前方向行驶的距离，y表示行驶方向
		if(s==0&&y!="South")
      //如果在北极点不往南走
		{
			cout<<"NO"<<endl;return 0;
        //不合法，直接输出走人
		}
		if(s==20000&&y!="North")
      //如果在南极点不往北走
		{
			cout<<"NO"<<endl;return 0;
        //不合法，直接输出走人
		}
		if(y=="South")s+=x;
      //如果当前向南走，纬度加
		if(y=="North")s-=x;
      //如果当前向北走，纬度减
		if(s<0||s>20000
      //如果走出了南极点或北极点
		{
			cout<<"NO"<<endl;return 0;
        //不合法，直接输出走人
		}
	}
	if(s==0)cout<<"YES"<<endl;
   //如果走完后在北极点，方案合法
	else cout<<"NO"<<endl;
   //如果走完后不在北极点，方案不合法
	return 0;
   别忘了return 0的好习惯
}



```

弱鸡刚开始写题解，求通过（万分感谢）



---

## 作者：一只大龙猫 (赞：1)

不知大家是否发现，数据范围**其实很小**。

数据保证 $1 \le n\le 50$ 且 $1 \le t_i \le 10^6$，也就是说，总路程最多只有 $50 \times 10^6=5 \times 10^7$ 千米。

这就是说，我们完全可以**一步一步模拟**而不会超时。

定义变量 $s$ 为 Limak 到北极的距离。若 $s=0$，则 Limak 在北极；若 $s=20000$，则 Limak 在南极。

在模拟每一步时，判断当前 Limak 的方向和位置是否合法。若 $s=0$ 且方向不为向南，或 $s=20000$ 且方向不为北，则描述无效，可以直接输出`NO`，退出程序。

当方向为向南或向北时，要记得改变 $s$ 的值。向南则 $s \gets s+1$，向北则 $s \gets s-1$。

注意最后要记得判断 Limak 是否在北极（即 $s$ 是否为 $0$）。

代码如下。

```cpp
#include<iostream>
#include<string>
using namespace std;
int n,s=0;//因为Limak从北极出发，所以s一开始为0 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int t;
		string dir;
		cin>>t>>dir;
		for(int i=1;i<=t;i++){
			if((s==0&&dir!="South")||(s==20000&&dir!="North")){
				cout<<"NO";
				return 0;
			}
			if(dir=="South"){
				s++;
			}
			if(dir=="North"){
				s--;
			}
		}
	}
	if(s!=0){
		cout<<"NO";
	}else{
		cout<<"YES";
	}
	return 0;
}
```

---

## 作者：zljhenry (赞：1)

这道题坑还挺多的：

1. 不需要考虑东西方向的移动，因为这是一个完全球体，只需要考虑南北方向。
2. 在北极点上只能想南移动，在南极点上只能向北移动。
3. 如果向南移动越过了南极点，也不成立，就像第 29 个数据点。
4. 可能会认为转了很多圈，所以说要把里程取模，但是事实上不需要，因为向一个方向走20000米就会因为第三个坑而被否定。

这样就可以写出代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int x,num=0,flag=1;// num 用来记录里程，flag 用来记录是不是不符合题意。
	for(int i=1;i<=n;i++){
		char a[10];
		cin>>x;cin>>a;//这里可以只判断首字母。
		if(a[0]=='S'&&num==20000) flag=0;//在南极点且要往南走，排除。
		else if(a[0]=='N'&&num==0) flag=0;//在北极点且要往北走，排除
		else if((a[0]=='E'||a[0]=='W')&&(num==20000||num==0)) flag=0;//在南极或北极点且要往西或东走，排除
		else if(a[0]=='S'&&num+x>20000) flag=0;//向南越过南极点，排除
		else if(a[0]=='N'&&num-x<0) flag=0;//向北越过北极点
		else if(a[0]=='S') num+=x;//以北极点为0，累计里程 
		else if(a[0]=='N') num-=x;
	}
	if(num!=0) flag=0;//判断最终是否是在北极点
	if(flag==0) cout<<"NO";
	else cout<<"YES";
	return 0;
}
```


---

## 作者：流绪 (赞：1)

模拟走的过程,看看最后有没有回到起点,或者走到的非法的位置

我们用一个 flag 变量来标记过程是否合法,然后就是模拟走的过程了，我们边读边做,往东往西走的情况不用考虑，因为你往东或者往西，你离北极的南极的距离还是一样的，想象一下地球仪...所以他对答案无影响,然后就根据往南往北来更新路程了，同时判断它合不合法就好了。

最后有一点很重要!如果你在北极或者南极，那么就需要考虑往东或往西了！因为在北极只能往南,在南极只能往北！

下面是 AC 代码，细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int flag = 1,sum=0;
	for(int i=1;i<=n;i++)
	{
		int x;
		char s[10];
		cin >> x >> s;
		if(!sum && s[0]!='S')
			flag = 0;//在起点只能往南走
		if(sum==20000&&s[0]!='N')
			flag = 0;南极只能往北
		if(s[0]=='N')
			sum-=x;
		if(s[0]=='S')
			sum+=x;//记录路程
		if(sum<0||sum>20000)
			flag = 0;//路程不合法
	} 
	if(!flag||sum)
		cout << "NO\n";
	else 
		cout << "YES\n";
	return 0; 
}  
```


---

## 作者：TheShuMo (赞：0)

## 思路
这道题根据翻译其实很好理解的。

因为题目说了，这个地球可以看做是一个完美的球形，所以我们无论往东走还是往西走，都是对判断有没有在北极往北走之类的没有任何影响。

所以我们可以直接忽略这部分的输入。分析往北走和往南走的各种情况。

- 在北极点时只能往北走，即若当前位置在北极，但输入为往北走时可以直接输出并结束。

- 在南极点时只能往南走，否则输出。

- 若走过了南极点或北极点，即当前位置超过了范围，输出并结束。


然后把这些要点模拟到程序里就好了。

## Code
```
#include<bits/stdc++.h>
using namespace std;int n,wz;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        string a;int b;
        cin>>b>>a;
        if(wz==0&&a[0]!='S'){cout<<"NO";return 0;}//判断
        if(wz==20000&&a[0]!='N'){cout<<"NO";return 0;}//判断
        if(a[0]=='S')wz+=b;//判断
        if(a[0]=='N')wz-=b;//判断
        if(wz>20000||wz<0){cout<<"NO";return 0;}//判断
    }if(wz>0)printf("NO");//还是**的判断
    else printf("YES");
    return 0;//模拟水题，完结撒花✿✿ヽ(°▽°)ノ✿
}
```

---

## 作者：zct_sky (赞：0)

### Solution:
-----
主要思路：模拟。

因为地球是一个完美的球体，所以无论往东走几公里或往西走几公里距离北极/南极的距离都是不变的。所以我们只需考虑往南和往北走。

接下来，只需列出要输出 $\texttt {NO}$ 的情况即可。这几种情况如下：

+ 站在北极不往南走
+ 站在南极不往北走
+ 直接走过南/北极，因为走过也有一瞬间站在南/北极点上，所以也符合以上情况
+ 最后没回到北极

### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
#define re register
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}
int n,x,t; 
string s;
int main(){
	n=read();
	for(int i=0;i<n;i++){
		t=read();cin>>s;
		if(x==0&&s!="South"){//站在北极不往南走
			puts("NO");
			return 0;
		}
		if(x==40000&&s!="North"){//站在南极不往北走
			puts("NO");
			return 0;
		}
		if(s=="North")x-=t;
		if(s=="South")x+=t;
		if(x<0||x>40000){//直接走过南/北极
			puts("NO");
			return 0;
		}
	}
	if(x==0) puts("YES");
	else puts("NO");//最后没回到北极
	return 0;
}
```

---

## 作者：jxbe6666 (赞：0)

### 题意

给你一串行走的路径，判断是否合法。

-----

### 思路

-----

$\text{North}\  $北 ，$\text{South} \ $南，$\text{West} \ $西，$\text{East} \ $东。

- 模拟：只有 $ 4 $ 种情况不符合
	1. 站在北极点不往南走
	2. 站在南极点不往北走
	3. 直接走过南/北极点，因为走过也有一瞬间站在点上，所以按照上面规则处理
	4. 最后没回到北极点

### 代码

-----

```c++
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
const ll N = 1e6 + 5;
const ll M = 1e3 + 5;
ll a[N], b[N], dp[N], n, m, x, y, z, k, l, r, t, f, ans;
bool flag;
string s1, s2;
stack<int> _s;
queue<int> _q;
map<int, int> _m;
ll quickpower(ll x, ll y, ll mod)
{ // 快速幂
    if (y)
    {
        ll div = quickpower(x, y >> 1, mod);
        if (y & 1)
            return (div * div) % mod * x % mod;
        else
            return div * div % mod;
    }
    return 1;
}
inline ll read()
{ // 快读
    ll x = 0, y = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        y = (c == '-') ? -1 : 1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x * y;
}
inline void out(ll x)
{
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        out(x / 10);
    putchar(x % 10 + '0');
}
inline void write(ll x, char ch)
{ // 快输
    out(x);
    putchar(ch);
}
int main()
{
    // North 北
    // South 南
    // West 西
    // East 东
    n = read();
    for (int i = 1; i <= n; i++)
    {
        m = read();
        cin >> s1;
        if (x == 0 && s1 != "South") // 北极点
        {
            flag = 1;
            break;
        }
        if (x == 20000 && s1 != "North") // 南极点
        {
            flag = 1;
            break;
        }
        if (s1 == "North")
        {
            x -= m;
            if (x < 0) // 过了北极点
            {
                flag = 1;
                break;
            }
        }
        if (s1 == "South")
        {
            x += m;
            if (x > 20000) // 过了南极点
            {
                flag = 1;
                break;
            }
        }
    }
    if (x || flag)
        puts("NO");
    else
        puts("YES");
    I AK IOI
}
```


---

## 作者：kaceqwq (赞：0)

# 题目大意：
我们假设地球是一个完全圆的球，它的表面是一个完美的球体。赤道和任何子午线的长度正好为 40000 公里。因此，从北极到南极或从南极到北极的旅行需要 20000 公里。Limak从北极开始送 n 个包裹，每次朝着  “North”，“South”，“West”，“East”四个方向之一前进 $a_i$ 公里。
并且符合以下规定：

• 如果在任何时候 Limak 在北极，他只能向南移动。

• 如果在任何时候 Limak 在南极，他只能向北移动。

• 旅程必须在北极结束。

检查是否满足上述条件，并输出 “YES” 或 “NO” 

# 分析：
首先分析题意，可以知道这一题的主要思路就是**模拟**，接着根据“地球表面是一个完美的球体”可以得知：无论 Limak 如何向东西移动，对结果都并没有影响，所以我们只需判断南北移动即可。最后根据题意模拟：先输入，然后考虑每一个不满足上述条件的情况，如果有一种情况满足，就输出 “NO” 。反之输出 “YES” 
。

# Code：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a[55],sum;  //sum记录总路程
bool flag;   //用来判断是否符合条件
string ch;
int main()
{
	ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i]>>ch;   //由于东西南北的英文首字母各不相同，所以直接判断首字母即可
    	if(ch[0]!='S'&&!sum)  //如果在北极不向南走，不行
    	flag=1;
    	if(ch[0]!='N'&&sum==20000)  //如果在南极不向北走，不行
    	flag=1;
    	if(ch[0]=='S')   //如果向南走，总路程就加上这次路程
    	sum+=a[i];
    	if(ch[0]=='N')   //如果向北走，总路程就减去这次路程
    	sum-=a[i];
    	if(sum<0||sum>20000)   //如果 Limak 超过了南北极点，不行
    	flag=1; 
	}  
	if(sum!=0)    //如果 Limak 最后没有回到北极，也不行
	flag=1;
	if(!flag)     //如果都符合条件，输出 “YES” 
	cout<<"YES"<<'\n';
	else          //否则输出 “NO” 
	cout<<"NO"<<'\n';
    return 0;
}

```


---

## 作者：Node_Edge (赞：0)

一道模拟的好题，，有以下条件：

1. 如果在任何时候（在任何指示之前或在执行其中一项指示时）Limak 在北极，他只能向南移动。

2. 如果在任何时候（在任何指示之前或在执行其中一项指示时）Limak 在南极，他只能向北方移动。

3. 旅程必须在北极结束。

由此可得，只考虑南极点、北极点的问题，所以东西方向没有用。

**代码分享**

```cpp
#include<iostream>
#include<string>
using namespace std;
int l;//latitude缩写 
int main() {
	ios::sync_with_stdio(false);//关闭同步 
	int n;
	cin>>n;
	while(n--) {
		int m;//metre缩写 
		string s;
		cin>>m>>s;
		if(l==0&&s!="South") { //不符合条件 1
			cout<<"NO"<<endl;
			return 0;
		}
		if(l==20000&&s!="North") { //不符合条件 2
			cout<<"NO"<<endl;
			return 0;
		}
		if(s=="South") { //纬度加 
			l+=m;
		}
		if(s=="North") { //纬度减 
			l-=m;
		}
		if(l<0||l>20000) { //走出极点 
			cout<<"NO"<<endl;
			return 0;
		}
	}
	if(l>0) { //不符合条件 3
		cout<<"NO";
	} else {
		cout<<"YES";
	}
	return 0;
}
```


---

## 作者：xiaomuyun (赞：0)

# CF750B New Year and North Pole 题解
[题目传送门](https://www.luogu.com.cn/problem/CF750B)
## 大致题意
有一个人，一开始在北极。已知从北极到南极的直线距离为 $20000$ 公里，且这个人可以向东南西北四个方向走任意距离。不过有可能他向北走到北极时还要往北走，但是比北极没有更北的地方了。所以这种走法是无效的。现在给出这个人的动作，求走法是否有效（**注意，在最后这个人一定要回到北极，否则也无效**）
## 题目分析
模拟。但是需要注意：实际上我们并不需要模拟这个人向东西两个方向走，但是我们还是需要判断，如果这个人在北极或南极时，**是没有东和西的**，所以还要特判一下。

当然，如果你在往北走的过程中走到北极了，但是还要往北走，这个动作也是无效的。所以我们在模拟的过程中需要判断是否会超过界限。
## 代码实现
```cpp
//position<10000时表示这个人在北半球,position>10000时表示这个人在南半球 
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;
int n,position=0;//一开始这个人在北极，position是位置
void ret(bool flag){
	if(flag) printf("YES\n");
	else printf("No\n");
	exit(0);
}
int main(){
	scanf("%d",&n);
	for(int i=1,distance;i<=n;++i){//distance是距离
		string direction;//direction是方向
		scanf("%d",&distance);
		cin>>direction;
		if((!position||position==20000)&&(direction=="West"||direction=="East")) ret(false);//如果在南极或北极要向东或西走的话，这种走法是无效的
		if(direction=="West"||direction=="East") continue;//并不需要模拟这个人向东西方向走
		if(direction[0]=='N'){//向北走的情况
			if(!position) ret(false);
			if(position-distance<0) ret(false);
			position-=distance;
		} else {//向南走的情况
			if(position==20000) ret(false);
			if(position+distance>20000) ret(false);
			position+=distance;
		}
	}
	ret(!position);//如果这个人在北极，即position为0，就是有效的
	return 0;
}
```

---

## 作者：Noby_Glds (赞：0)

这是一道又水又坑的模拟题。
### 思路:
我们发现，经度在这道题中没有任何用，那我们就直接用 $road$ 存储**利马克的位置离北极有多远**。

如果是朝南走，就用 $road$ 加上路程，朝北走就减去路程。

判断这个描述不合法有以下条件。

$1$，结束时不在北极，转换一下就是 $road$ 最终不等于 $0$。

$2$，在南极或北极向不是北或不是南的方向走。

把第二个条件转换一下就是在 $road$ 等于 $0$ 或 $20000$ 时向东走或向西走，或者 $road$ 小于 $0$ 或大于 $20000$。

判断一下就好了。
### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,road;
string y;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		if(y[0]=='S') road+=x;
		if(y[0]=='N') road-=x;
		if(road<0||road>20000||((y[0]=='W'||y[0]=='E')&&(road==0||road==20000))){
			cout<<"NO";
			return 0;
		}
	}
	if(road!=0) cout<<"NO";
	else cout<<"YES";
	return 0;
}
```


---

