# 【MX-X7-T0】[LSOT-3] 嗯欧哎

## 题目背景

原题链接：<https://oier.team/problems/X7A>。

嗯欧哎是欧哎界的知名比赛。本题可以用来检验嗯欧哎是否发挥出了真实水平。

此名称纯属虚构，不影射任何现实中的比赛或机构的名称。如有雷同，纯属巧合。

## 题目描述

一天的嗯欧哎有三道题，每道题的得分均在 $0 \sim 100$ 之间。定义一道题的得分在 $85 \sim 100$ 之间（含 $85$ 和 $100$，下同）时该题近似通过，在 $45 \sim 84$ 之间时为高分暴力，在 $25 \sim 44$ 之间时为低分暴力，在 $1 \sim 24$ 之间时为指数级暴力，若为 $0$ 分则认为是爆零。

一场发挥出真实水平的嗯欧哎有以下四种情况：
- 一道题高分暴力加一道题低分暴力加一道题指数级暴力；
- 一道题近似通过加一道题高分暴力加一道题低分暴力；
- 两道题近似通过加一道题低分暴力或高分暴力；
- 三道题近似通过。

给出一个人一天的嗯欧哎三道题的得分 $a,b,c$，求是否发挥出真实水平。

## 说明/提示

**【样例解释 #1】**

第一题的得分在 $45 \sim 84$ 之间，为高分暴力。

类似地，第二题为高分暴力，第三题为指数级暴力。

因为不符合题目里描述的任何一种，所以输出 `No`。

**【样例解释 #2】**

第一题和第三题为近似通过，第二题为低分暴力。满足“两道题近似通过加一道题低分暴力或高分暴力”的条件，所以输出 `Yes`。

**【数据范围】**

对于全部的数据，$0\le a,b,c\le 100$。

## 样例 #1

### 输入

```
50 50 10
```

### 输出

```
No```

## 样例 #2

### 输入

```
100 30 100
```

### 输出

```
Yes```

# 题解

## 作者：4041nofoundGeoge (赞：6)

## 思路

非常简单，直接记录档次，然后判断即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[5]={};
	int j,g,d,z,b;//五个计数器
	j=g=d=b=z=0;
	for(int i=1;i<=3;i++){
		cin>>a[i];
		if(a[i]>=85&&a[i]<=100)j++;
		else if(a[i]>=45&&a[i]<=85)g++;
		else if(a[i]>=25&&a[i]<=44)d++;
		else if(a[i]>=1&&a[i]<=24)z++;//档次
		else b++;
	}
	if((g==1&&d==1&&z==1)||(j==1&&g==1&&d==1)||(j==2&&(d==1||g==1))||(j==3))puts("Yes");//依题意判断
	else puts("No");
	return 0;
}
```

---

## 作者：jiqihang (赞：6)

~~话说题目的谐音是不是 NOI。~~

本题无思维难度，仅仅较为考验耐心，代码部分可以复制粘贴。

本题关键在于分支结构。

本题我们输入 $a,b,c$ 后，对于每个题目的分数，我们划分一下档次（近似通过、高分暴力、低分暴力、指数级暴力），然后在对应档次题数上加 $1$。

然后我们依据每个档次题目数，判定是否满足四种发挥正常情况即可。

思考：为什么不用判定爆零的情况的个数？

答案：本题四种发挥正常情况中没有与爆零个数相关的题目数要求。且每种情况非爆零题数加一起正好是 $3$，也就是如果发挥正常，不会有爆零题数。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,AC,GF,DF,ZS;
int main()
{
	cin>>a>>b>>c;
	if(a>=85) AC++;
	if(a>=45 && a<=84) GF++;
	if(a>=25 && a<=44) DF++;
	if(a<=24) ZS++;
	//a题
	if(b>=85) AC++;
	if(b>=45 && b<=84) GF++;
	if(b>=25 && b<=44) DF++;
	if(b<=24) ZS++;
	//b题
	if(c>=85) AC++;
	if(c>=45 && c<=84) GF++;
	if(c>=25 && c<=44) DF++;
	if(c<=24) ZS++;
	//c题
	if((GF==1&&DF==1&&ZS==1)||(AC==1&&GF==1&&DF==1)||(AC==2&&DF==1)||(AC==2&&GF==1)||(AC==3)) cout<<"Yes";
	else cout<<"No";
    //判断是否满足条件
 } 
```

---

## 作者：AFO_Lzx (赞：2)

本题特别简单，只需要用到分类讨论的判断即可。这个嗯欧哎，值得严查。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[5];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
	
	for (int i = 1; i <= 3; i++) {
		cin >> a[i];
		if (a[i] >= 85 && a[i] <= 100) c1++;
		if (a[i] >= 45 && a[i] <= 84) c2++;
		if (a[i] >= 25 && a[i] <= 44) c3++;
		if (a[i] >= 1 && a[i] <= 24) c4++;
		if (a[i] == 0) c5++;
	}
	
	if (c2 == 1 && c3 == 1 && c4 == 1) cout << "Yes";
	else if (c1 == 1 && c2 == 1 && c3 == 1) cout << "Yes";
	else if (c1 == 2 && (c2 == 1 || c3 == 1)) cout << "Yes";
	else cout << (c1 == 3 ? "Yes" : "No");
	
	return 0;
}
```

---

## 作者：_Jocularly_ (赞：1)

直接判断每个数字的情况，按照情况分类讨论，分支结构输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt1,cnt2,cnt3,cnt4,cnt5;
int a,b,c;
void check(int n){
    if(n >= 85 && n <= 100) cnt1 ++;
    else if(n >= 45 && n <= 84) cnt2 ++;
    else if(n >= 25 && n <= 44) cnt3 ++;
    else if(n) cnt4 ++;
    else cnt5 ++;
}
int main(){
    cin >> a >> b >> c;
    check(a),check(b),check(c);
    if(cnt2 == 1 && cnt3 == 1 && cnt4 == 1){
        cout << "Yes";
    }else if(cnt1 == 1 && cnt2 == 1 && cnt3 == 1){
        cout << "Yes";
    }else if(cnt1 == 2 && cnt2 == 1){
        cout << "Yes";
    }else if(cnt1 == 2 && cnt3 == 1){
        cout << "Yes";
    }else if(cnt1 == 3){
        cout << "Yes";
    }else cout << "No";
    return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：1)

## 解题思路：
模拟。把 `a,b,c` 对应的档次记录下来，逐一判断即可。
## CODE：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a, num[4];
int main()
{
    for (int i = 1; i <= 3; i++)
    {
        cin >> a;
        if (a == 0)
        {
            cout << "No";
            return 0;
        }
        if (a >= 85) num[i] = 4;
        else if (a >= 45) num[i] = 3;
        else if (a >= 25) num[i] = 2;
        else num[i] = 1;
    }
    sort(num + 1, num + 4);
    if (num[1] == 1 && num[2] == 2 && num[3] == 3) cout << "Yes";
    else if (num[1] == 2 && num[2] == 3 && num[3] == 4) cout << "Yes";
    else if (num[1] >= 2 && num[2] == 4 && num[3] == 4) cout << "Yes";
    else cout << "No";
    return 0;
}
```

---

