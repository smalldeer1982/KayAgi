# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 1 1 1 1 99
```

### 输出

```
NO
```

# 题解

## 作者：infinities (赞：5)

思路：

- 直接暴力生成每一种情况

- 加入if语句判断是否有相等

- 有就输出YES，否则输出NO

- 本题大小写不限，no,yes等也对

先上“表”生成器（这里有待优化）：
```cpp
//cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("1.out","w",stdout);//程序运行完后从1.out文件里找表
	cout<<"a+b+c==d+e+f||a+c+d==b+e+f||b+c+d==a+e+f";
	for(char a='a';a<='f';a++)
	for(char b='a';b<='f';b++)
	for(char c='a';c<='f';c++)
	for(char d='a';d<='f';d++)
	for(char e='a';e<='f';e++)
	for(char f='a';e<='f';e++)//六个暴力循环枚举每一种诸如“if(a+b+c==d+e+f)”的语句
		if(a!=b&&a!=c&&a!=d&&a!=e&&a!=f&&b!=c&&b!=d&&b!=e&&b!=f&&c!=d&&c!=e&&c!=f&&d!=e&&d!=f&&e!=f
        //暴力判断保证六个字符不重复
		cout<<"||"<<a<<"+"<<b<<"+"<<c<<"=="<<d<<"+"<<e<<"+"<<f;//打成表录入1.out文件进行进一步暴力操作
	return 0;//完了
}
```

这是AC代码：

```cpp
//cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    if(a+b+c==d+e+f||a+c+d==b+e+f||b+c+d==a+e+f||b+c+d==e+f+a||b+c+d==f+e+a||b+c+e==d+f+a||b+c+e==f+d+a||b+c+f==d+e+a||b+c+f==e+d+a||b+d+c==e+f+a||b+d+c==f+e+a||b+d+e==c+f+a||b+d+e==f+c+a||b+d+f==c+e+a||b+d+f==e+c+a||b+e+c==d+f+a||b+e+c==f+d+a||b+e+d==c+f+a||b+e+d==f+c+a||b+e+f==c+d+a||b+e+f==d+c+a||b+f+c==d+e+a||b+f+c==e+d+a||b+f+d==c+e+a||b+f+d==e+c+a||b+f+e==c+d+a||b+f+e==d+c+a||c+b+d==e+f+a||c+b+d==f+e+a||c+b+e==d+f+a||c+b+e==f+d+a||c+b+f==d+e+a||c+b+f==e+d+a||c+d+b==e+f+a||c+d+b==f+e+a||c+d+e==b+f+a||c+d+e==f+b+a||c+d+f==b+e+a||c+d+f==e+b+a||c+e+b==d+f+a||c+e+b==f+d+a||c+e+d==b+f+a||c+e+d==f+b+a||c+e+f==b+d+a||c+e+f==d+b+a||c+f+b==d+e+a||c+f+b==e+d+a||c+f+d==b+e+a||c+f+d==e+b+a||c+f+e==b+d+a||c+f+e==d+b+a||d+b+c==e+f+a||d+b+c==f+e+a||d+b+e==c+f+a||d+b+e==f+c+a||d+b+f==c+e+a||d+b+f==e+c+a||d+c+b==e+f+a||d+c+b==f+e+a||d+c+e==b+f+a||d+c+e==f+b+a||d+c+f==b+e+a||d+c+f==e+b+a||d+e+b==c+f+a||d+e+b==f+c+a||d+e+c==b+f+a||d+e+c==f+b+a||d+e+f==b+c+a||d+e+f==c+b+a||d+f+b==c+e+a||d+f+b==e+c+a||d+f+c==b+e+a||d+f+c==e+b+a||d+f+e==b+c+a||d+f+e==c+b+a||e+b+c==d+f+a||e+b+c==f+d+a||e+b+d==c+f+a||e+b+d==f+c+a||e+b+f==c+d+a||e+b+f==d+c+a||e+c+b==d+f+a||e+c+b==f+d+a||e+c+d==b+f+a||e+c+d==f+b+a||e+c+f==b+d+a||e+c+f==d+b+a||e+d+b==c+f+a||e+d+b==f+c+a||e+d+c==b+f+a||e+d+c==f+b+a||e+d+f==b+c+a||e+d+f==c+b+a||e+f+b==c+d+a||e+f+b==d+c+a||e+f+c==b+d+a||e+f+c==d+b+a||e+f+d==b+c+a||e+f+d==c+b+a||f+b+c==d+e+a||f+b+c==e+d+a||f+b+d==c+e+a||f+b+d==e+c+a||f+b+e==c+d+a||f+b+e==d+c+a||f+c+b==d+e+a||f+c+b==e+d+a||f+c+d==b+e+a||f+c+d==e+b+a||f+c+e==b+d+a||f+c+e==d+b+a||f+d+b==c+e+a||f+d+b==e+c+a||f+d+c==b+e+a||f+d+c==e+b+a||f+d+e==b+c+a||f+d+e==c+b+a||f+e+b==c+d+a||f+e+b==d+c+a||f+e+c==b+d+a||f+e+c==d+b+a||f+e+d==b+c+a||f+e+d==c+b+a)
    //最后的“表”加进if语句
    cout<<"YES"<<endl;else//暴力判断是否相等
    cout<<"NO"<<endl;//不然就输出NO
    return 0;//那么这题就做完了
}
```
有两个点要提一下：
- 该程序有不少重复，诸位有追求的dalao可以自行优化一下，我比较懒，就算了

- 对于此题的难度，一些洛谷用户开了个大大的玩笑，相信绝大多数用户都对此深有感触，~~恶意评分可耻~~！！！！

---

## 作者：chufuzhe (赞：4)

### 题意：
问六个数能否分成两组，每组三个数，使得每组数和相等。
### 思路：
我们可以先计算出这六个数的总和，然后除以二，代表如果能分的情况下，每组的和。如果余数为一就直接输出NO，因为每组中都是整数，而如果余数为一每组就都是小数，显然是不行的。如果余数为零，再依次暴力枚举第一组中的三个数，如果三数序号不一样并且三数之和等于总和除以二，就可以分，输出YES，标记并返回。如果枚举完了都没有发现合法的分法，就输出NO。
### 代码：
```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
int a[6]; //定义数组
int main()
{
	ios::sync_with_stdio(false); //输入输出优化流
	bool ans=0; //表示最终的结果，如果是0就输出NO，如果是1就输出YES，初始为0
	int s=0; //总和
	for(register int i=0;i<6;i++)
	{
		cin>>a[i]; //输入
		s+=a[i]; //累加
	}
	if(s%2==0) //余数为零
	{
		s/=2; //如果能分的情况下，每组的和
		for(register int i=0;i<6;i++) //暴力枚举，表示第一组的一个数
			for(register int j=0;j<6;j++) //表示第一组的二个数
				if(i!=j) //前两个数序号不一样
					for(register int k=0;k<6;k++) //表示第一组的二个数
						if(i!=k && j!=k) //最后一个数和前两数序号不一样
							if(a[i]+a[j]+a[k]==s) //可以分，三数之和等于总和除以二
							{
								ans=1; //标记
								break; //返回
							}
	}
	if(!ans) puts("NO"); //输出
	else puts("YES");
	return 0;
}

```


---

## 作者：Dog_Two (赞：3)

你谷的用户真的会开玩笑，截至2018-06-19，本题的难度被评价为[提高+/省选]。

总共只有6个，就算是最差的n！效率都能轻易水过——
于是我们来考虑n！做法：

- 对6个数字作全排列，如果前三个数字之和恰好等于总和的一半，那么输出YES；

需要注意的是，存在总和为奇数的情况，此时一定输出NO。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[7],sum=0;
    for(int i=1;i<=6;++i) cin>>a[i],sum+=a[i];
    if(sum&1){
        puts("NO");
        return 0;
    }
    sort(a+1,a+6);
    bool if_ans=false;
    do{
        int val=a[1]+a[2]+a[3];
        if_ans=val==sum/2;	
    }while(next_permutation(a+1,a+6) and !if_ans);
    puts(if_ans?"YES":"NO");
    return 0;
}
```

---

## 作者：hello2020 (赞：2)

不正常，难度总评提高+/省选-

这里提供一种O(n^3)的方法，暴力枚举6个数里面的三个

_~~**tai水了这题，暴力模拟**~~_

**下贴代码：**
```
#include<iostream>//头文件不可忘

using namespace std;

int main(){
	
        int a[7],sum=0;
	    for (int i=1;i<=6;i++)
	      cin>>a[i],sum+=a[i];
	    if (sum%2==1){
	      cout<<"NO"<<endl;//特判奇数总和
	      return 0;
	    }
	    sum/=2;
	    for (int i=1;i<=4;i++)
	      for (int j=i+1;j<=5;j++)
	        for (int k=j+1;k<=6;k++)
	          if (a[i]+a[j]+a[k]==sum){
	      	    cout<<"YES"<<endl;//看出来暴力了吧
	          	return 0;
		      }
    	cout<<"NO"<<endl;
	    return 0;//KO！
}
```

---

## 作者：AmaZingFantasy (赞：0)

题意：
给出 $6$ 个数，问能不能分成总和都相等并且每组都有 $3$ 个数的的两组。

提到“分成两组”时，可以这么想：只计算第一组的学生。只要他们的能力值总和等于总能力值的一半，就证明存在满足要求的分组方法。所以我们可以使用深度优先搜索算法来解决此题，枚举是否要将这名学生分到第一组即可。

 DFS 具体思路如下：

- 定义一个变量 $he$ 用于记录这六个人的能力值总和。

- 定义一个函数参数 $sum$，用来记录搜索到这一个学生时之前所有学生的能力值之和。定义一个全局变量 $cnt$，用来记录一共选了多少个学生来到第一组。每次根据这名学生是否进到第一组的情况对这些变量进行修改。

- 如果 $cnt$ 等于 $3$ 并且 $sum$ = $he \div 2$。则证明分组成功。输出 $\texttt{YES}$ 并退出程序。如果将所有方法搜索完之后，依然没有找到正解，输出 $\texttt{NO}$ 并结束即可。

注：如果 $he$ 是奇数，直接输出 $\texttt{NO}$。因为根本不能将它分为完全相等且不为小数的两个数。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long l;
l arr[6];
l he;
l cnt=0;
void dfs(l step,l sum){
    if(step >= 6 || sum > he/2){//如果超出范围就该剪枝了。
        return;
    }
    if(cnt==3 && sum==he/2){//满足这个条件就证明有正解了。
        cout<<"YES";
        exit(0);//exit(0)是cstdio特有的函数，可以结束整个程序。
    }
    //以下计算加上这个人的情况
    cnt++;
    dfs(step+1,sum+arr[step]);//深搜过去。
    cnt--;//回溯
    //以下计算不加上这个人的情况
    dfs(step+1,sum);//直接下一步。
    return;
}
int main(){
    for(l i=0;i<6;i++){
        cin>>arr[i];//输入
        he+=arr[i];//将he加上数组的这一项。
    }
    if(he % 2 != 0){//如果he是奇数，输出NO
        cout<<"NO";
    }else{
        dfs(0,0);//深搜
        cout<<"NO";
        /*
        如果深搜成功，会直接输出YES并退出程序，
        不会走到这里，所以只有没有正解时才会走到
        这一步。输出NO。
        */
    }
    return 0;
}

```


---

## 作者：jijidawang (赞：0)

## 题面简述

> 给定 $a_1,a_2,a_3,a_4,a_5,a_6$，保证 $a_1,a_2,a_3,a_4,a_5,a_6 \le 10^4$，求是否能将它们分成相等两组使每组内每数之和相等。

## 算法分析

$6$ 个数，分成相同两组，每组肯定是 $3$ 个，（排列组合算出方案数），可以枚举：

每组可能的情况：

$(a_1,a_2,a_3),(a_1,a_2,a_4),(a_1,a_2,a_5),(a_2,a_3,a_4),(a_2,a_3,a_5),(a_3,a_4,a_5)$

知道这 $6$ 个三元组后两两枚举 $\mathcal{O}(1)$，要枚举 $5!$ 次。

当然你也可以利用 `freopen` 打个小小的表，然后复制到 `if` 语句里水过这道题。

---

