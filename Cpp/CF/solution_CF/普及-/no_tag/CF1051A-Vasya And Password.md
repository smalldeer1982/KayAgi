# Vasya And Password

## 题目描述

Vasya came up with a password to register for EatForces — a string $ s $ . The password in EatForces should be a string, consisting of lowercase and uppercase Latin letters and digits.

But since EatForces takes care of the security of its users, user passwords must contain at least one digit, at least one uppercase Latin letter and at least one lowercase Latin letter. For example, the passwords "abaCABA12", "Z7q" and "3R24m" are valid, and the passwords "qwerty", "qwerty12345" and "Password" are not.

A substring of string $ s $ is a string $ x = s_l s_{l + 1} \dots s_{l + len - 1} (1 \le l \le |s|, 0 \le len \le |s| - l + 1) $ . $ len $ is the length of the substring. Note that the empty string is also considered a substring of $ s $ , it has the length $ 0 $ .

Vasya's password, however, may come too weak for the security settings of EatForces. He likes his password, so he wants to replace some its substring with another string of the same length in order to satisfy the above conditions. This operation should be performed exactly once, and the chosen string should have the minimal possible length.

Note that the length of $ s $ should not change after the replacement of the substring, and the string itself should contain only lowercase and uppercase Latin letters and digits.

## 说明/提示

In the first example Vasya's password lacks a digit, he replaces substring "C" with "4" and gets password "abcD4E". That means, he changed the substring of length 1.

In the second example Vasya's password is ok from the beginning, and nothing has to be changed. That is the same as replacing the empty substring with another empty substring (length 0).

## 样例 #1

### 输入

```
2
abcDCE
htQw27
```

### 输出

```
abcD4E
htQw27
```

# 题解

## 作者：xhhhh36 (赞：3)

### [传送门](https://www.luogu.com.cn/problem/CF1051A)
# 思路
首先我们要先统计数字，小写字母和大写字母的出现次数。然后我们可以发现，在这个字符串中，三种字符至少含有一种。为了防止多次统计字符的**出现次数**，每种字符都用两个变量来存储他们最后两次出现的**位置**。然后就分类讨论就可以了。替换的时候可以使用任意字符。
## 具体分类
1. 如果原串只含有一种字符。因为**原串的长度** $\ge3$，所以只需要将那种字符出现的任意两个位置，我用了最后两个位置，分别替换成缺少的那两种字符即可。
2. 如果原串含有两种字符，那么就从这两种字符中选择**出现次数** $\ge2$ 的字符，替换成缺少的那个字符。这样可以保证替换后这种字符还有。
3. 如果原串含有三种字符，那么**直接输出**即可。
# AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
char s[101];
int t,a,b,c,a1,b1,c1,a2,b2,c2;
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>s;
		a=b=c=0;
		for (int i=0;i<strlen(s);i++)
		{
			if ('0'<=s[i]&&s[i]<='9') a++,a2=a1,a1=i;
			else if ('a'<=s[i]&&s[i]<='z') b++,b2=b1,b1=i;
			else if ('A'<=s[i]&&s[i]<='Z') c++,c2=c1,c1=i;
		}
		if (a!=0&&b!=0&&c!=0)//如果原串含有三种字符
		{
			cout<<s<<endl;
			continue;
		}
		if (a==0)
		{
			if (b==0)//如果只有大写字符
			{
				s[c1]='0';
				s[c2]='a';
			}
			else
			{
				if (c==0)//如果只有小写字符
				{
					s[b1]='0';
					s[b2]='A';
				}
				else//如果只缺数字
				{
					if (b>=2)//小写字符数量足够
					{
						s[b1]='0';
						b1=b2;
					}
					else//大写字符数量足够
					{
						s[c1]='0';
						c1=c2;
					}
				}
			}
		}
		else
		{
			if (b==0)
			{
				if (c==0)//如果只有数字
				{
					s[a1]='a';
					s[a2]='A';
				}
				else//如果只缺小写字符
				{
					if (a>=2)//数字数量足够
					{
						s[a1]='a';
						a1=a2;
					}
					else//大写字符数量足够
					{
						s[c1]='a';
						c1=c2;
					}
				}
			}
			else//如果只缺大写字符
			{
				if (a>=2)//数字数量足够
				{
					s[a1]='A';
					a1=a2;
				}
				else//小写字符数量足够
				{
					s[b1]='A';
					b1=b2;
				}
			}
		}
		cout<<s<<endl;
	}
	return 0;
}
```


---

## 作者：KobeBeanBryantCox (赞：1)

# CF1051A Vasya And Password 题解

------------

[题目传送门](https://www.luogu.com.cn/problem/CF1051A)

------------

## 题意

给出 $T$ 个字符串 $s$，请以最少的修改次数将其变成至少有 $1$ 个大写字母、$1$个小写字母及 $1$ 个数字的字符串，输出修改过后的字符串 $s$。

很明显，有多种修改方案。所以本题不用看样例，只需要输出其中一种修改方案就行了。

------------

## 分析

首先我们需要**统计数字、小写字母和大写字母分别出现的个数**。

方便说明，这里将数字、小写字母和大写字母表述为类型。

### 1. 何时需要修改？

当某一类型的**出现个数为 $0$ 时**，说明这个类型是缺少的，需要修改原串。

- 比如 `abcABC`，缺少数字，就要修改原串的某一字符，让它变成某一数字，比如让原串变成 `0bcABC`。

### 2. 修改的方式

很明显，不能在原串随便一个位置乱修改，我们举个例子：

- `abcA` 缺少数字，如果你把原串改成 `abc0` 是不是又缺少大写字母了？

所以，我们要在原串里找一个字符，使得这个**字符的类型的出现次数大于等于 $2$**，这样修改过后，当前字符的类型的出现次数就大于等于 $2-1=1$，也就不会出现以上情况了。

还有，我们可以修改某一字符为任意数字或字母，为方便起见，我们**将数字修改为 `'0'`，小写字母修改为 `'a'`，大写字母修改为 `'A'`**。

### 3. 如何实现？

#### —— 统计每个类型出现的个数

```cpp
cnt1=0,cnt2=0,cnt3=0;
// cnt1 表示数字出现的个数 
// cnt2 表示小写字母出现的个数
// cnt3 表示大写字母出现的个数 
for(int i=0;i<s.size();i++) // 统计个数 
	if(s[i]>='0'&&s[i]<='9')cnt1++;
	else if(s[i]>='a'&&s[i]<='z')cnt2++;
	else cnt3++;
```

#### —— 修改原串

```cpp
if(!cnt1) // 如果缺数字 
{
	for(int i=0;i<s.size()&&!cnt1;i++)
		if(s[i]>='a'&&s[i]<='z'&&cnt2>=2)s[i]='0',cnt1++,cnt2--;
		// 如果是小写字母并符合条件 cnt2>=2 ，将当前字符变为数字 
		else if(s[i]>='A'&&s[i]<='Z'&&cnt3>=2)s[i]='0',cnt1++,cnt3--; // 如果大写字母则同理 
} // 以下同理 
if(!cnt2)
{
	for(int i=0;i<s.size()&&!cnt2;i++)
		if(s[i]>='0'&&s[i]<='9'&&cnt1>=2)s[i]='a',cnt2++,cnt1--;
		else if(s[i]>='A'&&s[i]<='Z'&&cnt3>=2)s[i]='a',cnt2++,cnt3--;
}
if(!cnt3)
{
	for(int i=0;i<s.size()&&!cnt3;i++)
		if(s[i]>='0'&&s[i]<='9'&&cnt1>=2)s[i]='A',cnt3++,cnt1--;
		else if(s[i]>='a'&&s[i]<='z'&&cnt2>=2)s[i]='A',cnt3++,cnt2--;
}
```

- 注意 1：`for(int i=0;i<s.size()&&!cnt1;i++)` 这一句里有一个 `!cnt1`，是因为当你修改了以后，`cnt1` 的个数已经不是 $0$ 了，就没必要继续循环了。下面两个循环同理。

- 注意 2：一定不能用 `else if`，我们再举个例子：

	- `aaa` 缺少数字，修改完后变成 `0aa`，如果这时候用了 `else if` 那么剩下还缺少的大写字母就不会被修改。

	正确的方法是 `aaa` 先修改为 `0aa` ，再修改为 `0Aa`。

- 注意 3：`if(s[i]>='a'&&s[i]<='z'&&cnt2>=2)s[i]='0',cnt1++,cnt2--;` 这一句最好要有 `cnt1++,cnt2--`。再举个例子：

	- 对于`aa`，`cnt1=0,cnt2=2,cnt3=0`，如果没有那一句，修改数字后则会变为 `0a`，且当前所有 `cnt` 还是原来的数值。

    此时还需修改大写字母，但是当我们扫描到字符 `'a'` 时，会认为 `cnt2` 还是大于等于 $2$，然后把 `'a'` 换成 `'A'`，这样小写字母就没有了。

    有人会说，那 `aa` 这种情况不是没有解吗？是的，无解，但是题目保证了 $s(3\leq|s|\leq100)$，即没有这种情况。
        
    虽然没有这种情况，但是我们还是最好把 `cnt1++,cnt2--` 加上，养成良好的习惯。

------------

## AC代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
int t,cnt1,cnt2,cnt3;
string s;
int main()
{
	cin>>t; // t 组字符串 
	while(t--)
	{
		cin>>s;
		cnt1=0,cnt2=0,cnt3=0;
		// cnt1 表示数字出现的个数 
		// cnt2 表示小写字母出现的个数
		// cnt3 表示大写字母出现的个数 
		for(int i=0;i<s.size();i++) // 统计个数 
			if(s[i]>='0'&&s[i]<='9')cnt1++;
			else if(s[i]>='a'&&s[i]<='z')cnt2++;
			else cnt3++;
		if(!cnt1) // 如果缺数字 
		{
			for(int i=0;i<s.size()&&!cnt1;i++)
				if(s[i]>='a'&&s[i]<='z'&&cnt2>=2)s[i]='0',cnt1++,cnt2--;
				// 如果是小写字母并符合条件 cnt2>=2 ，将当前字符变为数字 
				else if(s[i]>='A'&&s[i]<='Z'&&cnt3>=2)s[i]='0',cnt1++,cnt3--; // 如果大写字母则同理 
		} // 以下同理 
		if(!cnt2)
		{
			for(int i=0;i<s.size()&&!cnt2;i++)
				if(s[i]>='0'&&s[i]<='9'&&cnt1>=2)s[i]='a',cnt2++,cnt1--;
				else if(s[i]>='A'&&s[i]<='Z'&&cnt3>=2)s[i]='a',cnt2++,cnt3--;
		}
		if(!cnt3)
		{
			for(int i=0;i<s.size()&&!cnt3;i++)
				if(s[i]>='0'&&s[i]<='9'&&cnt1>=2)s[i]='A',cnt3++,cnt1--;
				else if(s[i]>='a'&&s[i]<='z'&&cnt2>=2)s[i]='A',cnt3++,cnt2--;
		}
		cout<<s<<"\n";
	}
	return 0;
}
```

------------

后记 1：版权所有 @[wangjianbo123](https://www.luogu.com.cn/user/865625)，请勿抄袭代码

后记 2：写代码的习惯一定要好，这种习惯养成了后，刷再难一点的题就没有细节错误了。代码不要乱七八糟，优秀的码风是很醉人的~

~~还有，能不能不要脸地要个赞呀~~

---

## 作者：_buzhidao_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1051A)
# 解题思路
首先我们需要**统计大写字母，小写字母和数字的数量**。  
如果个数为 $0$，需要补一个。  
但我们不能**拆东墙补西墙**，也就是说**缺一个数字，把唯一的大写字母改掉了**，等于白改，还浪费一个次数。~~这应该就是题目所说的 hack 吧。~~  
## 具体做法
**每修改一次之前**，都需要统计一次，记录每种字符**出现的次数和位置**。  
~~其实随便选一个就可以，~~ 这里选用**最后一次出现的位置**。  
只要**有一种字符出现的次数 $\ge2$**，就可以把**那种字符中的一个**替换掉。这里采用 `a`，`A`，`0` 替换别的字符，然后**直接输出更改后的字符串**就行了。  
## 解法证明
对于每种字符**我们只替换一次**，而且只有当另一种字符**被替换后还有至少一个同类型的字符存在**才会替换。  
根据数据范围 $(3\le|s|)$，可以证明**不会出现不能替换的情况**，所以该解法是最优的。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;string s;
int cnta,cntb,cntc,ia,ib,ic;
//a表示小写字母，b表示大写字母，c表示数字 
void count(){//统计大写字母，小写字母和数字的数量 
	cnta=0,cntb=0,cntc=0;
	ia=-1,ib=-1,ic=-1;
	for(int i=0;i<s.size();++i){
		if(s[i]>='a'&&s[i]<='z') cnta++,ia=i;
		if(s[i]>='A'&&s[i]<='Z') cntb++,ib=i;
		if(s[i]>='0'&&s[i]<='9') cntc++,ic=i;
	}
}
void th(int m){
	char w;if(m==1)w='a';if(m==2)w='A';if(m==3)w='0';//替换成什么 
	count();
	//替换↓ 
	if(cnta>=2){//只要能替换 
		s[ia]=w;//就替换 
	}
	else if(cntb>=2){//同理 
		s[ib]=w;
	}
	else if(cntc>=2){
		s[ic]=w;
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>s;count();
		if(cnta==0)th(1);if(cntb==0)th(2);if(cntc==0)th(3);//如果需要替换，就替换 
		cout<<s<<endl;
	}
	return 0;
} 
```


---

## 作者：XBaiC (赞：0)

### 思路

首先遍历一遍字符串。

看缺什么字符。

分情况讨论：

1. 不缺字符：输出字符串。

2. 缺一个字符：寻找最多类型字符的任意一个字符进行替换，并输出字符串。

3. 缺两个字符：表示此字符串只有一个类型字符。仅需修改前两个字符，并输出字符串。

CODE 较为简单，这里就不放了。

---

## 作者：liulianLL (赞：0)

# CF1051A Vasya And Password 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1051A)

注意到询问次数 $T$ 与字符串长度都较小，可以直接对字符串进行扫描，统计出大写字母、小写字母与数字各自出现的次数与位置。在扫描结束后，若大写字母、小写字母与数字有一种未出现过，则再找出一种出现多于一次的字符类型，并修改其中的一个字符。

具体实现细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,pos[4][110],s[4];
string st;
int main()
{
	scanf("%d",&T);
	while(T--){
		cin>>st;
		memset(pos,0,sizeof(pos));
		s[1]=0;s[2]=0;s[3]=0;
		for(int i=0;i<st.size();i++){
			if(st[i]>='A'&&st[i]<='Z'){
				s[1]++;
				pos[1][s[1]]=i;
			}
			else if(st[i]>='a'&&st[i]<='z'){
				s[2]++;
				pos[2][s[2]]=i;
			}
			else if(st[i]>='0'&&st[i]<='9'){
				s[3]++;
				pos[3][s[3]]=i;
			}
		}
		if(s[1]==0){
			if(s[2]>1){
				st[pos[2][s[2]]]='A';
				s[2]--;
			}
			else{
				st[pos[3][s[3]]]='A';
				s[3]--;
			}
		}
		if(s[2]==0){
			if(s[1]>1){
				st[pos[1][s[1]]]='a';
				s[1]--;
			}
			else{
				st[pos[3][s[3]]]='a';
				s[3]--;
			}
		}
		if(s[3]==0){
			if(s[1]>1){
				st[pos[1][s[1]]]='0';
				s[1]--;
			}
			else{
				st[pos[2][s[2]]]='0';
				s[2]--;
			}
		}
		cout<<st<<endl;
	}
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

## CF1051A Vasya And Password 题解
### 题意简述
本题因为没有翻译，我读了几遍后才完全理解。

给出一个字符串 $s$，以最少的修改次数将其变成至少有 $1$ 个大写字母、$1$ 个小写字母及 $1$ 个数字的字符串。

不要看题目给出一大长串，又有什么子串什么的，其实内容很简单。

### 做法分析
1. 关于修改方式

这题肯定不止一种修改方法，你看样例可能看不出什么规律。这就对了，样例只是其中一种方式，你不一定要按样例来，只要正确即可。（因为这题有 SPJ）如果你愿意，你甚至可以用 `rand()` 生成随机数。我这里就用最常用的 `A`、`a` 和 `0` 了。

2. 如何判断

显然，对于这题，我们是一定要统计三种字符出现的次数了，只需要枚举一下即可，作为“普及-”难度的题，是肯定不会超时的，代码如下：

```cpp
int a=0, b=0, c=0;
for(int i=0;i<s.size();++i)
	if(s[i]>='A' && s[i]<='Z') a++;
	else if(s[i]>='a' && s[i]<='z') b++;
	else c++;
```

3. 修改方法

显然对于每一种缺失的情况，我们都需要处理，因此这里要用并列关系的判断，不能用 `else` 这样的判断方法。

找到了缺失情况，是肯定要处理的，那么如何处理呢？我们应该从剩下的两种字符类型中找到一种出现次数大于 $1$ 的字符来替换。

问题来了：为什么要大于 $1$？

因为若这种字符出现了 $0$ 次，我们是肯定不能将其中的一个字符替换为缺失字符的。而如果这种字符只出现了 $1$ 次，替换后这种字符又没有了，所以也不行。

代码如下：

```cpp
if(a==0){
	if(b>1){
		for(int i=0;i<s.size();++i)
		if(s[i]>='a' && s[i]<='z'){ s[i]='A'; break; }
	}else{
		for(int i=0;i<s.size();++i)
		if(s[i]>='0' && s[i]<='9'){ s[i]='A'; break; }
	}
}
```

（另外两种的情况类似）

4. 输出

直接 `cout<<s<<endl;` 即可。

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	while(n--){
		string s;
		cin>>s;
		int a=0, b=0, c=0;
		for(int i=0;i<s.size();++i)
			if(s[i]>='A' && s[i]<='Z') a++;
			else if(s[i]>='a' && s[i]<='z') b++;
			else c++;
		if(a==0){
			if(b>1){
				for(int i=0;i<s.size();++i)
				if(s[i]>='a' && s[i]<='z'){ s[i]='A'; break; }
			}else{
				for(int i=0;i<s.size();++i)
				if(s[i]>='0' && s[i]<='9'){ s[i]='A'; break; }
			}
		}
		if(b==0){
			if(a>1){
				for(int i=0;i<s.size();++i)
				if(s[i]>='A' && s[i]<='Z'){ s[i]='a'; break; }
			}else{
				for(int i=0;i<s.size();++i)
				if(s[i]>='0' && s[i]<='9'){ s[i]='a'; break; }
			}
		}
		if(c==0){
			if(a>1){
				for(int i=0;i<s.size();++i)
				if(s[i]>='A' && s[i]<='Z'){ s[i]='0'; break; }
			}else{
				for(int i=0;i<s.size();++i)
				if(s[i]>='a' && s[i]<='z'){ s[i]='0'; break; }
			}
		}
		cout<<s<<endl;
	}
}
```

---

## 作者：czrjx (赞：0)

## 题意

输入 $n$ 个字符串，要求通过修改使每个字符串都有至少各 $1$ 个大写字母、小写字母和数字。

## 思路

对于每个字符串，先扫一遍判断出大写字母、小写字母和数字的个数分别为多少。

1. 若大写字母、小写字母和数字的个数均大于 $0$，则说明没有缺失成分，直接输出原字符串。

2. 若大写字母、小写字母、数字的个数中其中有一个为 $0$，则选取字符串中数量最多的字符种类，将其的一个字符修改为所缺失的字符。

3. 若大写字母、小写字母、数字的个数中有两个均为 $0$，说明原字符串中只有一种字符，可直接将字符串的前两个字符分别改为缺失的字符。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1010];
void in()
{
	int i,l,x=0,y=0,z=0,s=0,r=rand()%26;
	memset(a,0,sizeof(a));
	scanf("%s",a);
	l=strlen(a);
	for(i=0;i<l;i++)
	{
		if(a[i]>=48&&a[i]<=57)
			x++;
		if(a[i]>=65&&a[i]<=90)
			y++;
		if(a[i]>=97&&a[i]<=122)
			z++;
	}
	if(x==0) 	//判断缺失的字符种类的数量
		s++;
	if(y==0)
		s++;
	if(z==0)
		s++;	
	if(s==0)	//无缺失的情况
		printf("%s\n",a);
	if(s==2)	//缺失两种的情况
	{
		if(x>0)
		{
			a[0]=65+r;
			a[1]=97+r;
		}
		if(y>0)
		{	
			a[0]=48+rand()%10;
			a[1]=97+r;
		}
		if(z>0)
		{
			a[0]=48+rand()%10;
			a[1]=65+r;
		}
		printf("%s\n",a);
	}
	if(s==1)	//缺失一种的情况
	{
		if(x==0)
		{
			if(y>z)
			{
				for(i=0;i<l;i++)
					if(a[i]>=65&&a[i]<=90)
					{
						a[i]=48+rand()%10;
						break;
					}
			}
			else
			{
				for(i=0;i<l;i++)
					if(a[i]>=97&&a[i]<=122)
					{
						a[i]=48+rand()%10;
						break;
					}
			}
		}
		if(y==0)
		{
			if(x>z)
			{
				for(i=0;i<l;i++)
					if(a[i]>=48&&a[i]<=57)
					{
						a[i]=65+r;
						break;
					}
			}
			else
			{
				for(i=0;i<l;i++)
					if(a[i]>=97&&a[i]<=122)
					{
						a[i]=r+65;
						break;
					}
			}
		}
		if(z==0)
		{
			if(x>y)
			{
				for(i=0;i<l;i++)
					if(a[i]>=48&&a[i]<=57)
					{
						a[i]=97+r;
						break;
					}
			}
			else
			{
				for(i=0;i<l;i++)
					if(a[i]>=65&&a[i]<=90)
					{
						a[i]=97+r;
						break;
					}
			}
		}
		printf("%s\n",a);
	}
}
int main()
{
	srand((int)time(0));	//因为题目采用 Special Judge，所以可以用随机数进行修改
	int n;
	cin>>n;
	while(n--)
		in();
}
```


---

## 作者：zwyyy (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1051A)

~~我又写了这题的翻译，那也顺便写个题解吧。~~

## 思路
首先由题目可以知道，我们要将输入的字符串修改成包含至少一个数字，一个大写字母和一个小写字母的字符串并输出。

那么我们就可以想到将字符串中的字符遍历一遍后看看有几个数字、大写字母和小写字母。之后再根据缺少的字符替换就行了。

这里我记录了第二个出现的数字、大写字母和小写字母（如果有的话）。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105][105];
int b[105][105];
int d, x, n, d2, x2, n2;
void find(int a){
	int len = strlen(s[a]);
	d = x = n = d2 = x2 = n2 = 0;
	for(int i = 0; i < len; ++i){
		if(s[a][i] >= 'A' && s[a][i] <= 'Z'){
			++d;
			if(d == 2)	d2 = i;
			b[a][i] = 1;
		}
		else if(s[a][i] >= 'a' && s[a][i] <= 'z'){
			++x;
			if(x == 2)	x2 = i;
			b[a][i] = 2;
		}
		else if(s[a][i] >= '0' && s[a][i] <= '9'){
			++n;
			if(n == 2)	n2 = i;
			b[a][i] = 3;
		}
	}
}
void work(int a){
	find(a);
	if(d == 0){
		if(x2 != 0){
			s[a][x2] = 'A';
		}
		else{
			s[a][n2] = 'A';
		}
	}
	if(x == 0){
		if(d2 != 0){
			s[a][d2] = 'a';
		}
		else{
			s[a][n2] = 'a';
		}
	}
	if(n == 0){
		if(d2 != 0){
			s[a][d2] = '0';
		}
		else{
			s[a][x2] = '0';
		}
	}
	find(a);
	if(d && x && n){
		return;
	}
	else{
		work(a);
	}
}
int main(){
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		scanf("%s", s[i]);
		work(i);
		printf("%s\n", s[i]);
	}
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/121168552)

---

## 作者：_5t0_0r2_ (赞：0)

# 分析：
 
首先可以证明， 原密码至多缺 $2$ 种字符。

所以我们分类讨论：

若缺 $2$ 种字符，那么说明原密码都是由一种字符组成的，直接修改第 $1,2$ 个字符即可。

若缺 $1$ 种字符，那么，我们首先找出出现次数多的那种字符，并将第一个出现的这种字符修改为缺失的那种字符：因为出现次数少的那种字符可能只有 $1$ 个，替换后仍会缺失一种字符。而因为 $|s| \geq 3$，所以出现次数最多的那种字符至少有 $2$ 个，可以替换一个。

---

## 作者：__HHX__ (赞：0)

# 思路
扫描一遍字符串看缺什么。

不缺：直接输出字符串。

缺一个：寻找最多类型字符的任意一个字符进行替换。

缺两个：表示此字符串只有一个类型字符。仅需修改前两个字符。
# 代码
```cpp
#include<iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		bool f1 = 0, f2 = 0, f3 = 0;
		int cnt1 = 0, cnt2 = 0, cnt3 = 0, q1, q2, q3;
		string s;
		cin >> s;
		for(int i = 0; i < s.size(); i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				cnt1++, f1 = 1, q1 = i;
			}
			if (s[i] >= 'a' && s[i] <= 'z') {
				cnt2++, f2 = 1, q2 = i;
			}
			if (s[i] >= 'A' && s[i] <= 'Z') {
				cnt3++, f3 = 1, q3 = i;
			}
		}
		if(f1 + f2 + f3 == 2){
			if (!f1) {
				s[cnt2 > cnt3 ? q2 : q3] = '0';
			} else if(!f2) {
				s[cnt1 > cnt3 ? q1 : q3] = 'a';
			} else if(!f3) {
				s[cnt2 > cnt1 ? q2 : q1] = 'A';
			}
		} else if(!(f1 && f2 && f3)){
			s[0] = (f1 ? 'a' : '0'), s[1] = (f1 ? 'A' : (f2 ? 'A' : 'a'));
		}
		cout << s << '\n';
	}
}
```

---

## 作者：c1910903 (赞：0)

遍历一遍后把多的类型换成少的类型就做完了

遍历时对于每位，如果有需要（有类型没有）并且能换（这位上的类型换掉后还有）就换

这里类型指大写、小写与数字

------------
```cpp
%:pragma GCC optimize "-O3"
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
ll t,cnt[5];
bool flag;
string s;
inline void _read(ll &x){
	x=0;
    ll f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    x*=f;
    return;
}
inline void _print(ll x){
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>=10)
        _print(x/10);
    putchar(x%10+'0');
    return;
}
inline ll f(char c){
	if('0'<=c&&c<='9')
		return 0;
	else if('A'<=c&&c<='Z')
		return 1;
	else
		return 2;
}
int main(){
	_read(t);
	while(t--)
	{
		flag=0;
		cnt[0]=cnt[1]=cnt[2]=0;
		cin>>s;
		for(ll i=0;i<s.size();i++)
			cnt[f(s[i])]++;
		if(cnt[0]&&cnt[1]&&cnt[2])
			cout<<s;
		else if(!cnt[0]&&cnt[1]&&cnt[2])
		{
			for(ll i=0;i<s.size();i++)
				if(cnt[f(s[i])]>1&&!flag)
				{
					putchar('0');
					flag=1;
				}
				else
					putchar(s[i]);	
		}
		else if(cnt[0]&&!cnt[1]&&cnt[2])
		{
			for(ll i=0;i<s.size();i++)
				if(cnt[f(s[i])]>1&&!flag)
				{
					putchar('A');
					flag=1;
				}
				else
					putchar(s[i]);	
		}
		else if(cnt[0]&&cnt[1]&&!cnt[2])
		{
			for(ll i=0;i<s.size();i++)
				if(cnt[f(s[i])]>1&&!flag)
				{
					putchar('a');
					flag=1;
				}
				else
					putchar(s[i]);		
		}
		else if(!cnt[0]&&!cnt[1]&&cnt[2])
		{
			putchar('0');
			putchar('A');
			for(ll i=2;i<s.size();i++)
				putchar(s[i]);	
		}
		else if(!cnt[0]&&cnt[1]&&!cnt[2])
		{
			putchar('0');
			putchar('a');
			for(ll i=2;i<s.size();i++)
				putchar(s[i]);	
		}
		else if(cnt[0]&&!cnt[1]&&!cnt[2])
		{
			putchar('A');
			putchar('a');
			for(ll i=2;i<s.size();i++)
				putchar(s[i]);
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，我们需要用最少的修改次数使得字符串同时有大写、小写英文字母和数字。因为要求次数最少，所以只有输入字符串中没有某种字符时才需要修改 $1$ 个多余的字符种类为缺少的字符种类。由 $3<|s|$ 可知，如果有某种字符缺少，那么一定有某种字符多于一个。

首先创建 3 个列表存储每种字符的所有形式（应该也可以用 ASCII 码，~~但是我懒~~）。创建 3 个变量存储每种字符的数量。如果有某种字符的数量为 $0$，就找一个数量大于 $1$ 的字符类型修改成这种缺少的字符类型。修改后不需要改变每种字符数量，因为对剩下的过程没有影响。设最开始缺少的字符类型为 $a$，被修改的字符类型为 $b$，最后一种字符类型为 $c$。当 $c$ 的数量大于 $0$ 时，直接输出；当 $c$ 的数量为 $0$ 时，因为 $a$ 只有 $1$ 个，所以也不会修改 $a$ 为 $c$，所以只有修改 $b$ 为 $c$ 的情况。而本来就只有存储 $b$ 的数量的变量大于 $1$，所以不需要改变。

另外，每段输出间不换行会 RE。
## 代码
```python
a,b,c,d = int(input()),('0','1','2','3','4','5','6','7','8','9'),('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'),('A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z')
for m in range(a):
    e,f,g,h = list(input()),0,0,0
    for i in e:
        if i in b:
            f += 1
        elif i in c:
            g += 1
        else:
            h += 1
    if f == 0:
        if g > 1:
            for j in range(len(e)):
                if e[j] in c:
                    e[j] = 0
                    break
        else:
            for k in range(len(e)):
                if e[k] in d:
                    e[k] = 0
                    break
    if g == 0:
        if f > 1:
            for j in range(len(e)):
                if e[j] in b:
                    e[j] = 'a'
                    break
        else:
            for k in range(len(e)):
                if e[k] in d:
                    e[k] = 'a'
                    break
    if h == 0:
        if f > 1:
            for j in range(len(e)):
                if e[j] in b:
                    e[j] = 'A'
                    break
        else:
            for k in range(len(e)):
                if e[k] in c:
                    e[k] = 'A'
                    break
    for l in e:
        print(l,end='')
    print()
```

---

