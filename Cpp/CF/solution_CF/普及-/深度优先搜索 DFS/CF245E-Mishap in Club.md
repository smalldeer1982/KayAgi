# Mishap in Club

## 题目描述

Polycarpus just has been out of luck lately! As soon as he found a job in the "Binary Cat" cafe, the club got burgled. All ice-cream was stolen.

On the burglary night Polycarpus kept a careful record of all club visitors. Each time a visitor entered the club, Polycarpus put down character "+" in his notes. Similarly, each time a visitor left the club, Polycarpus put character "-" in his notes. We know that all cases of going in and out happened consecutively, that is, no two events happened at the same time. Polycarpus doesn't remember whether there was somebody in the club at the moment when his shift begun and at the moment when it ended.

Right now the police wonders what minimum number of distinct people Polycarpus could have seen. Assume that he sees anybody coming in or out of the club. Each person could have come in or out an arbitrary number of times.

## 样例 #1

### 输入

```
+-+-+
```

### 输出

```
1
```

## 样例 #2

### 输入

```
---```

### 输出

```
3```

# 题解

## 作者：L_zaa_L (赞：5)

## 题意
求进进出出的不同的人会有多少个。

也就是至少有几个人进过咖啡馆。

## 分析

我们不知道原来咖啡馆里有多少人，可以设。数据范围的确很小（也就一百）可以设一百甚至更大。当咖啡馆里的人达到顶峰的时候，就是说他最少有咖啡馆里的人数这么多不同的人。当人数最少时，最多的人数减去最少的也就是人口浮动至少有这么多人，因为题目叫我们求最少的不同的人，所以说当人数最少的时候，我们要把他当做咖啡馆没人了（毕竟咖啡馆原来有多少人我们是蒙的，这样是为了最少）。答案就是最大值减最小值。


## Code

不说了，看代码吧。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int n=s.size(),minx=1e+8,maxx=-1,p=200;//p是我随便设的，代表咖啡馆每个时刻有多少人
	for(int i=1;i<=n;i++){
		maxx=max(maxx,p);//求最大
		minx=min(minx,p);//求最小
		if(s[i-1]=='+') p++;
		else p--;//变换咖啡馆人数
	}
	maxx=max(maxx,p);
	minx=min(minx,p);
	cout<<maxx-minx;//求出答案
	return 0;
} 
```


---

## 作者：YuTianQwQ (赞：1)

# 题目解析

这段代码的目标是处理一个字符串，字符串只包含 '+' 和 '-' 两种字符。对于每个 '+'，我们认为它代表深度加一，对于每个 '-'，我们认为它代表深度减一。任务是找出这个字符串表示的最大深度。

## 解题思路

1. **读取输入**：首先，我们读取输入的字符串 `s`。

	`cin >> s;`

2. **初始化变量**：我们使用两个变量来分别记录当前深度 `pi` 和最大深度 `tp`。

	` int pi = 0, tp = 0; `

3. **遍历字符串**：我们遍历字符串的每一个字符。对于每个字符，如果它是 '+'，我们就将 `pi` 加一，并将 `tp` 更新为 `pi` 和 `tp` 的最大值；如果它是 '-'，我们就将 `pi` 减一。如果在 `pi` 为零的情况下遇到 '-'，我们将 `tp` 加一。

    ```cpp
    for(char c : s)
    {
        if(c == '+')
        {
            pi++;
            tp = max(tp, pi);
        }
        else
        {
            if(pi == 0) tp++;
            else pi--;
        }
    }
    ```

4. **输出结果**：完成所有字符的遍历后，输出最大深度 `tp`。

	`cout << tp;`

总的来说，这段代码通过遍历字符串的每一个字符，并根据字符的类型调整深度，找出字符串表示的最大深度。

# 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int pi = 0, tp = 0;
    for(char c : s)
    {
        if(c == '+')
        {
            pi++;
            tp = max(tp, pi);
        }
        else
        {
            if(pi == 0) tp++;
            else pi--;
        }
    }
    cout << tp;
    return 0;
}


---

## 作者：_zexal_ (赞：1)

## 题意
有个人记录了酒馆里面的人进出的次数，共 $n$ 次，问你最少可以通过几个人造成这样的情况。
## 思路
记录两个变量，一个负责记录里面的人，一个记录外面的人。初始时一个人都没有。

我们一共会遇到 $2$ 种情况需要添加人。第 $1$ 种，外面没有以前的人，却来了一个人，所以我们只能添加一个新人。第 $2$ 种，里面没有以前的人，却出去了一个人，所以我们也只能添加一个新人。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string s;
	int in=0,out=0;
	cin>>s;
	for(int i=0; i<s.size(); i++) {
		if(s[i]=='+') {
			in++;
			if(out) out--;
			else in++;

		} else {
			out++;
			if(in) in--;
			else out++;

		}
	}
	cout<<in+out;
	return 0;
}
```


---

## 作者：hopeless_hope (赞：1)

~~第一眼看还以为是DP呢。~~

仔细一看，原来是道水题。

## 题意

给定一个带有 "+" 与 "-" 的字符串，表示这个叫做 "Binary Cat" 的咖啡厅的人进出情况。

现在你是个保安，你要根据给你的字符串求出你见到了多少人。

"+" 代表进入；"-" 代表出去。

## 思路

用两个变量来存在咖啡厅中与咖啡厅外的人，根据题意模拟：

如果读到 "+" 则有一个**原本在咖啡厅外的人**进入了咖啡厅。

反之，读到 "-" 则有一个**原本在咖啡厅内的人**出了咖啡厅。

**特别地，我们需要注意，在一开始，咖啡厅内或外可能出现没人的情况，则是新来的人**


## 代码实现

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int main(){
    cin.tie(0);
    cout.tie(0);
    int ins=0,outs=0,len=0;
    string s;
    cin>>s;
    len=s.length();
    for(int i=0;i<len;i++){
        if(s[i]=='+'){
            ins++;
            if(outs) outs--;//特判此时咖啡厅外已经有人
        }
        else if(s[i]=='-'){
            outs++;
            if(ins) ins--; //特判此时咖啡内外已经有人
        }
    }
    cout<<ins+outs<<endl;
    return 0;
}
```


---

## 作者：zwye (赞：0)

### 题意
这题很容易理解。就是 `+` 表示有人进入， `-` 表示有人出去，让你求至少几人进出。

### 思路
用两个变量 $s$ 和 $t$ 记录咖啡厅内和外的人数。

第一种情况：如果读入 `+` 就是有外面的人进入了。（$s$ 加 1，$t$ 减 1）

第二种情况：如果读入 `-` 就是有里面的人出去了。（$s$ 减 1，$t$ 加 1）

### 代码
```c
#include<bits/stdc++.h>
using namespace std;
int s,t;
string n;
int main(){
	cin>>n;
	for(int i=0;i<n.size();i++)
    {
		if(n[i]=='+')
        {
			s++;//用ans统计进来的人 
			if(t!=0)t--;//抵消
		}
        else
        {
			t++;//用t来统计出去的人 
			if(s!=0)ans--;//抵消
		}
	}
	cout<<s+t;
	return 0;
}
```


---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF245E)

这题可以设一个变量表示在咖啡馆里的人数 $a$，再设一个变量表示曾来过咖啡馆但后来出去了的人数 $b$，最后设一个变量 $ans$ 表示答案。

这题有四种情况：当字符 $s_i$ 为 `+` 时，因为要求至少，所以如果曾来过的人足够则从其中来一个人，$a$ 加一，$b$ 减一。如果曾来过的人数不够，我们就得再找一个陌生人进入咖啡馆，此时代表答案的 $ans$ 加一，$a$ 也加一。

当字符 $s_i$ 为 `-` 时，因为要求至少，所以如果咖啡馆里的人足够则从其中拎出去一个人，$b$ 加一，$a$ 减一。如果咖啡馆里的人数不够，我们就得再生出一个陌生人使他在一开始时就在咖啡馆内，这样 $a$ 便等于 $1$，人数够，但这时不需要把 $a$ 赋值为 $1$，因为那个人必须得出去，所以 $a$ 照样为零。此时代表答案的 $ans$ 加一，$b$ 也加一。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a=0,b=0,ans=0;
char s[310];
int main()
{
    cin>>s;
    n=strlen(s);
    for(register int i=0;i<n;i++)
    	if(s[i]=='+')
    		if(b==0) a++,ans++;
    		else a++,b--;
    	else
    		if(a==0) b++,ans++;
    		else a--,b++;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 思路
既然题目中问的是至少，那么我们就可以分两种情况了，我们只需要用两个变量来记录出去过的人和进来过的人。

第一种情况此时进来一个人，如果之前没出去过人，就将进来的人加一，否则若之前出去过人就将出去的人减一。

第二种情况出去也同理，若出去一个人且之前没进来过人，就将出去的人加一，否则里面之前若有人，就将进来的人减一。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,ans1;
string s;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++) {
		if(s[i]=='+'){
			ans++; // 用ans统计进来的人 
			if(ans1) ans1--; // 抵消掉一个 
		}else {
			ans1++; // 用ans1来统计出去的人 
			if(ans) ans--; // 抵消掉一个 
		}
	}
	cout<<ans+ans1; // 输出未被抵消之和 
	return 0; // 完结散花 
}
```


---

## 作者：封禁用户 (赞：0)

## 思路
我们可以建两个变量，一个记录里面的人，一个记录外面的人。最开始一个人也没有。

有 $2$ 种情况需要添加人：
1. 外面没有以前的人，来了一个人，添加一个新人。
2. 里面没有以前的人，出去了一个人，添加一个新人。

## Code
```cpp
#include<bits/stdc++.h>

using namespace std;

string ch;
int x,y;

int main() 
{
	cin>>ch;	
	
	int len=ch.size();
	
	for(int i=0;i<len;i++) 
	{
		if(ch[i]=='+')//情况1 
		{
			x++;
            
			if(y>0) 
			{
				y--;
			}
		} 
		else//情况2
		{
			y++;	
            
			if(x>0) 
			{
				x--;
			}
		}
	}
	
	int k=x+y;//总人数 
	
	cout<<k;
	
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

通过题目的阅读知道了同一个人可以进出多次。

如果进来了人，而之前没有人出去，这说明肯定来了一个新的人进咖啡厅。

但是进来时有人出去过，也可能是之前来过的回头客。

反之，如果出来了人，而之前没有人进去去，这说明这个人一直在咖啡厅里面。

如果出来是有人进去过，那也可能是之前进去的人出来。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int cnt,tot;
int main(){
	cin>>a;
	for(int i=0;i<a.length();i++){
		if(a[i]=='+'){
			cnt++;//进来人的数量
			if(tot)
				tot--;
		}
		if(a[i]=='-')
		{
			tot++;//一直在里面人的数量
			if(cnt)
				cnt--;			
		}
	}
	cout<<tot+cnt;
}
```

---

## 作者：yyyymh (赞：0)

解释题目：给一个字符串，加号代表有人进入咖啡馆，减号代表有人走出咖啡馆，问最终至少有多少人进出过咖啡馆且一人可以进出多次

思路：输入字符串后求长度，一个一个遍历，我们可以定义两个变量存储里面的人和外面的人，我们争取把每一个进去的都认为是之前出去的同一个人，出入都同理，这需要我们在每次操作时判断里面或外面是否有人，如读到加号，如果外面的人的数量不为零，则认为是之前的一个人再次进入咖啡馆

代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	int sum1=0,sum2=0;
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]=='+'){
			sum1++;
			if(sum2)  sum2--;
		}
		else{
			sum2++;
			if(sum1)  sum1--;
		}
	}
	cout<<sum1+sum2;
	return 0;
}
```


---

