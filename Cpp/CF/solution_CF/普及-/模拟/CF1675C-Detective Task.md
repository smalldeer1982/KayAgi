# Detective Task

## 题目描述

Polycarp bought a new expensive painting and decided to show it to his $ n $ friends. He hung it in his room. $ n $ of his friends entered and exited there one by one. At one moment there was no more than one person in the room. In other words, the first friend entered and left first, then the second, and so on.

It is known that at the beginning (before visiting friends) a picture hung in the room. At the end (after the $ n $ -th friend) it turned out that it disappeared. At what exact moment it disappeared — there is no information.

Polycarp asked his friends one by one. He asked each one if there was a picture when he entered the room. Each friend answered one of three:

- no (response encoded with 0);
- yes (response encoded as 1);
- can't remember (response is encoded with ?).

Everyone except the thief either doesn't remember or told the truth. The thief can say anything (any of the three options).

Polycarp cannot understand who the thief is. He asks you to find out the number of those who can be considered a thief according to the answers.

## 说明/提示

In the first case, the answer is $ 1 $ since we had exactly $ 1 $ friend.

The second case is similar to the first.

In the third case, the suspects are the third and fourth friends (we count from one). It can be shown that no one else could be the thief.

In the fourth case, we know absolutely nothing, so we suspect everyone.

## 样例 #1

### 输入

```
8
0
1
1110000
?????
1?1??0?0
0?0???
??11
??0??```

### 输出

```
1
1
2
5
4
1
1
3```

# 题解

## 作者：Adolfo_North (赞：6)

思路（有点绕，慢慢品）：

- 最后一个说有的人前面的人一定不会是小偷，如果前面的人是嫌疑人，那么他进去的时候应该已经被偷了，他就说谎了。

- 第一个说没有的人后面的人一定不会是小偷，如果后面的人是嫌疑人，那么他进去的时候还没被偷，他就说谎了。

但是只有小偷会说谎，所以可以判断两种情况矛盾与否。

挑战最短代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a;
int main()
{
//	freopen("detective.in","r",stdin);
//	freopen("detective.out","w",stdout);
	int T;
	cin>>T;
	while(T--){
		cin>>a;
		int sizea=a.size();
		int left=0,right=sizea-1;
		for(int i=0;i<sizea;i++)if(a[i]=='1')left=i;
		for(int i=left;i<sizea;i++)if(a[i]=='0'){right=i;break;}  
		cout<<right-left+1<<endl;
	}
	return 0;
}
```


---

## 作者：qW__Wp (赞：5)

### 题目大意
房间里放了一幅画，有n个人依次进入，当他们都出来后画不见了，每个人可以告诉我们当时画的状态（ $1$，$0$，$?$ ）表示在，不在，不明，**只有小偷可以说假话**。小偷有且只有一个。输出**可能是小偷的**有多少个。
### 思路
通过贪心的策略，更新每一次小偷的人选。最后输出。

+ 如果第一个人说画没了，那么他一定是小偷。

+ 设样例为 $1?0$，则在 $1$ 到 $0$ 之间的人有嫌疑(包括 $1$ 和 $0$)。证明：设 $1$ 是小偷，则 $0$ 说的是真话。设 $0$ 是小偷，则 $1$ 说的是真话。设 $?$ 是小偷，则 $1$ 和 $0$ 说的都是真话，符合题意，故结论成立。

+ 设样例为 $11$，当运行到第 $2$ 个 $1$ 时可能的人选为第 $2$ 个 $1$。证明：若第一个 $1$ 是小偷，则第二个 $1$ 矛盾(画不在了)，若第二个 $1$ 是小偷，则第一个 $1$ 说的是真话，符合题意。故结论成立。

+ 若第一个人说的是 $0$，则他必是小偷，需特判。

+ 因题目限制，不可能出现先 $0$ 后 $1$ 的情况。若 $1$ 是小偷，则 $0$ 没说真话。若 $0$ 是小偷，则 $1$ 没说真话。

### 完整代码
```cpp
#include<iostream>
using namespace std;
int t,ans,l;
string s;
bool v;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>s;
		l=s.size();
		if(s[0]=='0'){
			cout<<'1'<<endl;
			ans=0;
			continue;
		}else{
			ans=1;
		}
		for(int j=1;j<l;j++){
			if(s[j]!='?'){
				if(s[j]=='0'){
					cout<<ans+1<<endl;
					v=true;
					break;
				}
				if(s[j]=='1'){
					ans=1;
				}
			}else{
				ans++;
			}
		}
		if(!v){
			cout<<ans<<endl;
		}
		v=false;
		ans=0;
	}
	return 0;
}
```

### 提醒

复制粘贴一时快，作弊标签两星期！

---

## 作者：住在隔壁小莘 (赞：4)

## 题意

房屋里有一幅画，$n$ 个人依次进入房间。前一个人出之后后一个人再进。$n$  个人都出房间后画不见了。每个人只知道自己是不是小偷和他在房间里时画还在不在。
现在审问这 $n$ 个人，每个人可以回答 `1` 表示他在房子里时画在,`0` 表示不在，`?` 表示忘了。小偷会随便回答一个答案，其他人是诚实的。
现在我们需要求出，有几个人可能是小偷。

### 分析

看到这里我们可以明白。
1. 小偷只有一个，只有小偷会说假话，其他人**一定**会说真话，但仅限于回答 `1` 或 `?` 。
2. 在小偷进行偷窃后，画的状态从没被偷变为被偷，那么不是小偷的人，我们称为诚实人，他们会说的话就从 `1` 或 `?` 变成 `0` 或 `?`，所以不存在 `0` 在 `1` 前面的情况。

#### 分类讨论
他每次不一定同时出现 `0` 和 `1` 和 `?`，所以进行分类讨论。

1. 只出现 `1`。
2. 只出现 `0`。
3. 只出现 `?`。
4. 出现 `1` 和 `0`。
5. 出现 `1` 和 `?`。
6. 出现 `0` 和 `?`。
7. 出现 `1` 和 `0` 和 `?`。

-  对于情况一，所有都是 `1`，那么只有最后一个才有可能说谎，如果是前面说谎，后面的都应该是 `0` 或者 `？`，只有最后一个才不影响前面的。

- 对于情况二，所有都是 `0`，则与情况一同理。

- 对于情况三，所有都是 `？`，那么我们无法判断，则所有人都有可能.

- 对于情况四，出现 `1` 和 `0`，那么只会有一种情况。
1. 例子:`111000`，说谎的只有可能是第三个人或者第四个人，第三个人是小偷后面也满足都变为 `0`，第四个人是小偷也都满足前面都是 `1`，后面都是 `0`。
2. 那么此时可能会有人问：我 `110100` 不行吗，不能算入这种情况吗？**这种情况不算入情况四**，你可以想想假如第三个人是小偷，那么第四个人就应该是 `0`，假如第四个人是小偷，那么第三个人就应该是 `1`，显然相矛盾，在题目中也有说**保证输入合法**，所以不必担心。

- 对于情况五，出现 `1` 和 `？`，那么我们只需要**从后往前**找，找到**第一个**  `1`，那么从这个位置往后且包括这个位置的都有可能是小偷。

- 对于情况六，出现 `0` 和 `？`，那么我们只需要**从前往后**找，找到**第一个**  `0`，那么从这个位置往前且包括这个位置的都有可能是小偷。

1. 像样例中的最后一个，可能会有人问：不应该是全部吗，就一个是 `0`，其他全都是 `？`。那这肯定是不对的，假如第四个是小偷，那么第三个就应该是 `1`，就不应该是 `0` 了啊。

- 对于情况七，出现 `1` 和 `0` 和 `?`，我们其实可以把 `?` 全部去掉，也就是所谓的不用管他，`?` 只是会影响小偷的可能数量,所以他跟情况四的判断方式是一样的。

接下来附上代码。

## Code：
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int t;
string str;
char a[1010000];
int main(){
	cin>>t;
	while(t--){
		cin>>str;
		int  len=str.length();
		int flag1=false,flag0=false,flag2=false;//flag2判断问号是否出现过
		for(int i=0;i<len;i++){
			a[i+1]=str[i];
			if(a[i+1]=='0'){
				flag0=true;
			}else if(a[i+1]=='1'){
				flag1=true;
			}else{
				flag2=true;
			}
		}
		if(flag2&&!flag0&&!flag1){//情况三
			cout<<len<<endl;
		}else if(flag1&&!flag0&&!flag2){//情况一
			cout<<1<<endl;
		}else if(flag0&&!flag1&&!flag2){//情况二
			cout<<1<<endl;
		}else if(flag1&&flag0&&!flag2){//情况四
			int first,last;
			for(int i=1;i<=len;i++){
				if(a[i]=='0'){
					first=i;
					break;
				}
			}
			for(int i=len;i>=1;i--){
				if(a[i]=='1'){
					last=i;
					break;
				}
			}
			cout<<abs(last-first)+1<<endl;//写成first-last+1也可以
		}else if(!flag1&&flag0&&flag2){//情况六
				for(int i=1;i<=len;i++){
					if(a[i]=='0'){
						cout<<i<<endl;
						break;
					}
				}
		}else if(flag1&&!flag0&&flag2){//情况五
			for(int i=len;i>=1;i--){
				if(a[i]=='1'){
					cout<<len-i+1<<endl;
					break;
				}
			}
		}else{//情况七
			int first,last;
			for(int i=1;i<=len;i++){
				if(a[i]=='0'){
					first=i;
					break;
				}
			}
			for(int i=len;i>=1;i--){
				if(a[i]=='1'){
					last=i;
					break;
				}
			}
			cout<<abs(last-first)+1<<endl;//同上
		}
	}
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/tet494fq.png)

谢谢大家的阅读

---

## 作者：FReQuenter (赞：4)

## 题意：

有 $n$ 个人依次进入了 $\text{Polycarp}$ 的房间。这之后，他发现房间里的一幅画被偷走了。他询问了那 $n$ 个人在他们进去时有没有那幅画。

- 每个人都会回答 “有” “没有” “不知道” 三种中的一种。

- 小偷的回答可能是真话也可能是假话，其他人的回答都是真话。

## 思路：

因为小偷偷走画前画还在，所以小偷前面所有的人都会说“有”“不知道”两种中的一种；

同样的思路，因为小偷偷走画后画不在，所以小偷后面所有的人都会说“没有”“不知道”两种中的一种；

综上所述，我们只需要找出最后一个说“有”的人和第一个说“没有”的人，夹在这两个人之间的人都有可能是小偷。这样做的时间复杂度和空间复杂度都是x线性的。

注意点：可以在最前面插入一个说“有”的人，在最后插入一个说“没有”的人，以免出现没有人说“有”或“没有”的情况。

## 代码（ $\text{C++}$ ）:

```cpp
#include<iostream>
#include<string>
using namespace std;
bool a[200005],b[200005];
//A数组表示第i个人是否是（最后一个及之前）说了“是”或“不知道”的人；
//同样，B数组表示第i个人是否是（第一个及之前）说了“不是”或“不知道”的人。
int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        a[0]=b[0]=true;
        //初始条件
        for(int i=0;i<s.length();i++)
            a[i+1]=a[i]&&(s[i]=='1'||s[i]=='?');
            //处理A数组:
            //等价于 if(a[i]==true&&(s[i]=='1'||s[i]==0)) a[i+1]=true;
            //如果要再优化（比如说抢最优解）可以在出现a[i]==false的时候break;
        for(int i=s.length()-1;i>=0;i--)
            b[s.length()-i]=b[s.length()-i-1]&&(s[i]=='0'||s[i]=='?');
            //和处理A数组一样的思想
        int ans=0;
        for(int i=0;i<s.length();i++)
            if(a[i]&&b[s.length()-i-1])
                ans++;
                //如果当前位置：
                //在说了“是”的人之后，
                //在说了“不是”的人之前，
                //则答案加一
                //当然如果还要优化，可以在出现第一个不符合时break;（因为以后肯定也不符合，所有可能的位置是连在一起的）
        cout<<ans<<'\n';//输出
    }
    return 0;
}
```

---

## 作者：zhangchengyan (赞：2)

$\texttt{Solution}$

### 思路简述

根据题意我们可以得知，只有一个人是小偷且他会说假话。

所以我们可以推断出：

- 小偷偷走之前的每个人会说 $1$ 或 $?$ 。

- 小偷偷走之后的每个人会说 $0$ 或 $?$ 。

综上，我们可以先统计出 $1$ 的个数记为 $t$ ，然后从头开始枚举，每次遇到一个 $1$ 就将 $t-1$ ，在循环的末尾加个判断：若当前 $1$ 的个数已经为 $0$ ，就将答案 $++$ 。

同时，若第 $i-1$ 个人说了 $0$ 时，我们直接退出循环，因为第 $i$ 个人以及他后面的人都说了真话。

**注意顺序结构！**

### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,t,ans;
string s;
int main()
{
	cin>>T;
	while(T--)
	{
		ans=0,t=0;
		cin>>s;
		int n=s.size();
		s=' '+s;//为了方便，下标[1..n]
		for(int i=1;i<=n;++i)
		  if(s[i]=='1')
		    ++t;//统计1的数量
		for(int i=1;i<=n;++i)
		{
			if(s[i-1]=='0')
			  break;//若这个人前面已经出现过0，则他一定说了真话
				//后面的每个人也是同理，都不是小偷，所以直接break
			if(s[i]=='1')
			  --t;//遇到1就将统计-1
			if(!t)
			  ++ans;//如果当前说1的没了，则他有可能说了假话，答案++
		}
		cout<<ans<<'\n';	    
	}
}
```


---

## 作者：user470883 (赞：2)

## 思路：

根据题意，我们可以知道小偷只有一个，只有小偷会撒谎，有三种回答“有”、“没有”和“不知道”。

根据只有小偷会撒谎，我们可以得知小偷前面的人会说“有”或者“不知道”，而在小偷后面的人会说“没有”或者“不知道”。

然后我们找出最后一个说“有”的人和第一个说“没有”的人，那么这样包括上句话给出的边界的范围内，有可能是小偷。而题目问的正是这个，框定范围后我们数一下就行了。

**注意事项：** 考虑到可能会出现全部说“有”或全部说“没有”的情况，可以在最前面插入一个说“有”的人或在最后插入一个说“没有”的人。

---

## 作者：WilliamFranklin (赞：2)

### 主要思路

这道题很简单（只要你的思维敏捷）。因为只可能有一个小偷，那么我们首先可以得出的是：只要谁看到过，那么他前面的人肯定是看到过的。同样，只要谁没看到过，那么他后面的人肯定是没有看见过的。

我们又可以发现，最后一个说看到的和第一个说没看到的很有可能就是小偷。如果最后一个说看到的和第一个说没看到的中间还有人，那么也有可能是他们。

所以我们只要找到最后一个说看到的和第一个说没看到的位置，然后在求出最后一个说看到的到第一个说没看到的一共有几个人即可（也算上最后一个说看到的和第一个说没看到的）。

好啦，贴代码。

### AC Code

```
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	string a;
	cin >> t;
	getchar();
	while(t--) {
		cin >> a;
		int i = 0;
		while (i < a.size()) {
			if (a[i] == '0') {
				break;
			}
			i++;
		}
		int j = a.size() - 1;
		while (j >= 0) {
			if (a[j] == '1') {
				break;
			}
			j--;
		}
		if (i >= a.size() && j < 0) {
			cout << a.size() << endl;
			continue;
		}
		if (i < a.size() && j >= 0) {
			cout << i - j + 1 << endl;
		} else {
			cout << i - j << endl;
		}
	}
}
```

可能会有一些地方讲得不详细，请大家指出，谢谢！

---

## 作者：cyrxdzj (赞：2)

### 一、思路

首先，小偷有且只有一个。

并且，非小偷一定会说真话（或者说不知道）。

于是，我们可以发现，如果某个人之前（不包括这个人）有人说没看到，则这个人一定不是小偷。

同理，如果某个人之后，有人说看到了，则这个人也一定不是小偷。

否则，这个人就有可能是小偷。

### 二、代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
char a[200005];
int n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",a+1);
		n=strlen(a+1);
		int one_count=0;//看到的人数
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]=='1')
			{
				one_count++;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(a[i-1]=='0')//前面有个没看到画的人
			{
				break;
			}
			if(a[i]=='1')
			{
				one_count--;
			}
			if(one_count==0)//后面没有看到画的人
			{
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：ryanright (赞：1)

## Description

Polycarp 买了一幅贵重的画作，并邀请了他的 $n$ 个朋友来看。$n$ 个朋友依次进入房间来看，每个时刻房间里最多只有一个人。

结果到最后画不见了。于是 Polycarp 挨个问他的朋友们进去时房间里有没有画，得到三种回答：有、没有或不知道。窃贼的回答任意，而其他人都说真话或是不知道。现在 Polycarp 想知道，有多少个朋友可能是窃贼？

## Solution
对于窃贼而言，有一个性质：窃贼前面的人都回答“有”或“不知道”，后面的人都回答“没有”或“不知道”，因为他们说的都是真话。

因此窃贼的位置一定在所有回答“有”的人的后面，所有回答“没有”的人的前面。也就是说，在最后一个回答“有”的人和第一个回答“没有”的人中间的人都有可能是窃贼，以及最后一个回答“有”的人和第一个回答“没有”的人，因为他们都满足上面那个性质，而其他人都不满足。

需要注意的是，如果没有人回答“有”，那么第一个回答“没有”及其前面的人有可能；同样的，如果没有人回答“没有”，那么最后一个回答“有”及其后面的人有可能。

## Code

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char str[1000005];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str + 1);
		int n = strlen(str + 1), l = 0, r = 0;
		for (int i = 1; i <= n; i++)
			if (str[i] == '1')
				l = i;
			else if (str[i] == '0' && !r)
				r = i;
		if (l && r)
			printf("%d\n", r - l + 1);
		else if (!l && !r)
			printf("%d\n", n);
		else if (l && !r)
			printf("%d\n", n - l + 1);
		else
			printf("%d\n", r);
	}
	return 0;
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

Polycarp 买了一副画摆在了房间的墙上，Polycarp 邀请了他的 $n$ 个朋友前来参观。每次他都让第 $i$ 个人进入房间，然后出来。但是所有人都参观完后，他发现画不见了！

现在 Polycarp 想知道有多少个人可能会是小偷。他让每位朋友都描述一个字符：

+ 若这个朋友看见了画，则为 `1`。

+ 若这个朋友没看见画，则为 `0`。

+ 若这个朋友不知道看没看见画，则为 `?`。

其中有一个真正的小偷一定会说谎。

请你帮助 Polycarp 找到一共有多少个人可能成为小偷。

### 基本思路

我们观察样例之后发现，正确且没人说谎，没有 `?` 的字符串总是由前面 $x$ 个 `1`，然后 `y` 个 `0` 组成。（$0\le x,y\le n\land x+y=n$）

若有人说谎，那么一定是 `1` 和 `0` 交界处的两个人。（也就是最后一个 `1` 和第一个 `0`）

而若有 `?` 夹在 `1` 和 `0` 中，那么这几个 `?` 都能够成为分界点，所以都要算。

而若 `?` 出现在其它地方，很容易证明其不可能是小偷。

### 代码

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
using namespace std;
const int Buffer_Size = 1 << 10;
namespace {
	char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
	inline char Next_Char() {
		if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
		return *ihead++;
	}
	template <typename T>
	inline void read(T &x) {
		x = 0; char ch = Next_Char(); T f = 1;
		while (!isdigit(ch)) f -= (ch == '-') << 1, ch = Next_Char();
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = Next_Char();
		x *= f;
	}
	template <typename T, typename ...L> inline void read(T &x, L &...y) {read(x), read(y...);}
	inline void readstr(string &s) {
		s = ""; char ch = Next_Char();
		while (ch == ' ' || ch == '\n') ch = Next_Char();
		while (ch ^ ' ' && ch ^ '\n') s += ch, ch = Next_Char();
	}
}
const int N = 2e5 + 5;
string s; int t;
signed main(void) {
	cin >> t; while (t--) {
		cin >> s; bool flg = 0; int n = s.size();
		int lst1 = 0, fst0 = n - 1;
		rep2(i, n - 1, 0) {
			if (s[i] == '1') {lst1 = i; break;}
		}
		rep1(i, 0, n - 1)
			if (s[i] == '0') {fst0 = i; break;}
		if (lst1 == -1 && fst0 == -1) {cout << n << endl; continue;}
		if (lst1 == -1 || fst0 == -1) {puts("1"); continue;}
		if (lst1 > fst0) {puts("1"); continue;}
		int ans = 0;
		cout << fst0 - lst1 + 1 << endl;
	}
}
```

---

## 作者：JZH123 (赞：0)

# 解题思路

1. 小偷有一个；
1. 不是小偷的人说的话一定是真话；
1. 对于每个人：如果这个人之前有人说没看到，或者在这个人之后，有人说看到了，那么这个人一定不是小偷；
1. 如果以上条件都不满足，这个人就有是小偷的可能。

# 上代码——


------------

```
#include <bits/stdc++.h>//万能头文件
using namespace std;
#define int long long//全部开long long,防止int不够
#define f(i, j, k) for (int i = j; i <= k; i ++)//宏定义
int t;
const int N = 2e5 + 5;//定义常量
char a[N];
signed main()//signed搭配"#define int long long"使用
{
	scanf("%d", &t);
	while(t --)
	{
		scanf("%s", a + 1);
		int n = strlen(a + 1);
		int c, answer;//c表示看到的人数, answer表示答案
		answer = c = 0;//初始化
		f(i, 1, n)
			if(a[i] == 49)
				c ++;
		f(i, 1, n)
		{
			if(a[i - 1] == 48)//前面有个没看到画的人， 48相当于字符0
				break;
			if(a[i] == 49)
				c --;
			if(!c)//后面没有看到画的人
				answer ++;
		}
		printf("%d\n", answer);//输出答案，记得换行
	}
	return 0;
}
```

---

## 作者：huajx (赞：0)

## 思路：
通过思考可以得知：小偷前面所有人的回答只可能是 ? 或 1，小偷后面所有人的回答只可能是 ? 或 0。

所以我们只要找出最后一个 1 的位置和第一个 0 的位置，求区间长度即可。

## 代码（C++）：
```
#include<bits/stdc++.h>
using namespace std;
int read(){char ch=getchar();int sgn=1,x=0;while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*sgn;}
long long t,n,w0,w1;//w0:第一个 0 的位置  w1:最后一个 1 的位置 
char a[200010];//字符数组爱好者 
int main(){
	cin>>t;//时间充裕，直接cin
	for(int i=0;i<t;i++){
		cin>>a;
		n=strlen(a);
		w0=n-1;w1=0;//初始化:处理仅有 ? , 0 或 1 的特殊情况 
		for(int j=0;j<n;j++){
			if(a[j]=='1')w1=j;//找到 1(标记) 
			else if(a[j]=='0'){w0=j;break;}//找到第一个 0 的位置(标记并退出) 
		}
		cout<<w0-w1+1;//计算区间长度并输出 
	}
	return 0;
}
```


---

## 作者：andrew2012 (赞：0)



------------

# Description


------------

 有一幅画，被 $n$ 个朋友陆续观赏（每个时刻房间里最多有一个人在看画）。而在最后，这幅画竟然神秘地消失了（被某个朋友偷走了）。现在给出每个朋友的回忆（‘1’代表画还在，‘0’代表画不在，‘？’代表不记得了），让你求出有哪些朋友可能是小偷。（共   $T$  组数据）

（非小偷一定会说真话（或者说不知道），小偷有可能说出三种回答中的任意一种）

------------


# Solution


------------

~~典型的数学烧脑题！~~

首先，小偷有且只有一个（只是问哪些朋友有可能是小偷，但真正的小偷肯定只有一个，总不可能2个人一起偷一幅画吧？把画切开？ qwq ~），并且，非小偷一定会说真话（或者说不知道）。于是可以发现，如果某个人之前（不包括这个人）有人说没看到，则这个人一定不是小偷。同理，如果某个人之后有人说看到了，则这个人也一定不是小偷，否则这个人就有可能是小偷。


------------

# Code(C++)


------------

```
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
const int N=2e5+5;//N=200005
int t,n;//t组数据，每次n个人
char a[N];//每个朋友的回答
int main()//主函数
{
	scanf("%d",&t);//或者写：cin>>t;
	while(t--)//或者写：for(int i=1;i<=t;i++)
	{
		scanf("%s",a+1);//或者写：cin>>a+1;
		n=strlen(a+1);//几个人 = 字符串的长度
		int cnt=0,ans=0;//ans个人可能是小偷，cnt个“画还在”回答
		for(int i=1;i<=n;i++)//字符串的每一个字符穷举循环
		{
			if(a[i]=='1')//回答“画还在”
				cnt++;//计数器cnt++
		}
		for(int i=1;i<=n;i++)//再次将字符串的每一个字符穷举循环
		{
			if(a[i-1]=='0')//前面有个没看到画的人
				break;//直接退出循环
			if(a[i]=='1')//有人回答“画还在”
				cnt--;//计数器cnt--
			if(cnt==0)//后面没有看到画的人
				ans++;//这个人有可能是小偷
		}
		printf("%d\n",ans);//或者写：cout<<ans<<endl;
	}
	//return 0;   //完结撒花！
}

```

```


---

