# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0```

### 输出

```
6
5```

# 题解

## 作者：锦时 (赞：78)


这是第一篇题解！！！鸡冻！！！
 
本题可以是一道应用暴搜加强力剪枝的极好的练习题，所以选择这道题的童鞋，在明白了思路及程序之后相信会有很大提升！
 
先来一下题目：

    乔治拿来一组等长的木棒，将它们随机的砍掉，得到若干根小木棍，然后他又想把这些木棍拼接起来，恢复到裁剪前的状态，但他忘记了初始时有多少木棒以及木棒的初始长度。请你设计一个程序，帮助乔治计算木棒的可能最小长度，每一节木棍的长度都用大于零的整数表示。
    
    输入包含多组数据，每组数据包括两行。第一行是一个不超过64的整数，表示砍断之后具有多少节木棍。第二行是截断以后，所得到的各节木棍的长度。在最后一组数据之后。是一个零。 
    
    对于每组数据，分别输出原始木棒的可能最小长度。
    
注意的问题是，各个原始木棒的长度都是一样的！

说一下本题的总思路即：DFS+超强力剪枝！（详见本人的 **AC** 程序）

首先，我们要从小到大枚举原始木棒的长度len，也就是枚举答案，最先找到的就是最小长度。那怎么确定枚举的是正确的呢？我们用的是搜索。

如果只搜索是极不理智的，而如果有了剪枝，一切就好说了，本题的剪枝主要有五个，我们会边看程序边了解一下。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int len,n;
bool v[101];
int a[101];
int cnt,sum,val;
//stick 即正在拼第stick根木棒(确保前面的都拼好了)
//第stick根木棒的当前长度为cab
//拼第stick根木棒的上一根小木棒为last(有些小朋友可能会有疑问，为什么第一次搜索是dfs(1,0,1)而不是dfs(1,0,0)首先，如果dfs(1,0,0)也能过并且更正确一些，而即使dfs(1,0,1)在bfs中的第三个if中，因为v[i]==1也不会进入)
bool dfs(int stick,int cab,int last)
{
	if(stick>cnt)
	  return true;//所有的木棒都已经拼好
	if(cab==len)
	  return dfs(stick+1,0,1); //当前的一根已经拼好，开始下一根
	int fail=0;//第二个剪枝开始了：对于每根木棒，fail记录的是最近一次尝试拼接的木棍长度。这样再回溯时就不会再尝试相同长度的木棍。
	for(int i=last;i<=n;i++)//第三个剪枝开始了：限制先后加入一根原始木棍的长度是递减的。因为先拼上一个长为x的木棍再拼上一个长为y的木棍，等效于先拼上一个长为y的木棍再拼上一个长为x的木棍。所以只需要搜索其中一种即可。
	{
		if(v[i]==0&&a[i]+cab<=len&&fail!=a[i])
		{
			v[i]=1;
			if(dfs(stick,cab+a[i],i))
			  return true;
		    v[i]=0;//还原搜索前的状态。
			fail=a[i];
			if(cab==0||cab+a[i]==len)
			  return false;//第四个剪枝开始了:如果在一根原始木棒中尝试拼接的第一根木棍的递归分支就以失败返回，直接判断当前分支无解。与此同时，第五个剪枝开始了，如果两个木棍的长度和与一个木棍的一样，只尝试一个的就行了(因为前两个可能会有更大的效用)
		}
	}
	return false;//所有分支都尝试过，搜索失败。
}
int main()
{
	while(cin>>n&&n)
	{
		sum=0;
		val=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			sum+=a[i];//为啥要累加尼？为了求原始木棒的根数，即sum/len(len是枚举的答案)
            val=max(val,a[i]);
		}
	    sort(a+1,a+n+1);//第一个剪枝开始了：此为优化搜索顺序，优先尝试较长的木棍
	    reverse(a+1,a+n+1);//sort从小到大排序，而reverse会将整个数组翻转(懒人做法)，这样就可以达到从大到小排的结果
	    for(len=val;len<=sum;len++)
	    {
	    	 if(sum%len)
	    	   continue;
	    	 cnt=sum/len;
	    	 memset(v,0,sizeof(v));
	    	 if(dfs(1,0,1))//(1,0,1具体是啥，看上方的dfs)
	    	   {
	    	    cout<<len<<endl;
	    	   	break;//确定枚举正确的第一次即为答案，立即结束
	    	   }   
	    }
	}
        return 0;
} 
```

---

## 作者：fletmer (赞：26)


## 首先这是一道DFS+剪枝的题目，关键在于对剪枝策略的确定，其次是注意思维的严密性（边界条件的确定，下一个状态搜索的位置，场景的复原）

#### 1.（约定木棒由木棍组成）累计长度是为了枚举木棒长度时便于计算木棒数，其次val取所有木棍最大长度（枚举起点），因为如果取得不是最大长度如从1开始枚举会导致个别木棍长直接超过当前木棒长，徒增搜索复杂度

#### 2.关于DFS函数：nbr表示当前算到第几根木棒，显然有边界nbr==x+1（x为当前枚举的木棒长度下木棒数）；len为当前计算的木棒已有长度，显然有边界len==t（t为当前枚举的木棒长度）；las为当前木棒上一根组成木棍的编号（剪枝，稍后讲解）

#### 3.关于剪枝：

一：对木棍长 从大到小的排序，是为了减小搜索树。可以想象先加入长的棍，再加入短的棍，相较于先加入短的棍后加入长的棍，搜索树大大减小

二：在main函数中已对木棒长进行了排序(从大到小)，在DFS函数中有一个变量“las为当前木棒上一根组成木棍的编号”，这是因为爆搜的时候对于两个不同长度的木棍x，y可能存在先加x后加y和先加y后加x两种显然等价的情况所以保证添加木棍的单调性显然是一种合理的剪枝。

三：关于fl变量：fl记录当前木棒最近一次添加的木棍长度。因为上一个剪枝中提到了保证单调性，此单调性体现为i<j，xi>=xj，所以倘若两相邻木棍长度相同，前一根木棍已然匹配失败，则再尝试后一根情况一样失败。所以fl就是为了避免两相邻木棍长度相同且重复同样的失败。

四：if(len==0) return false; 此句的意思是因为所有木棒长度相同皆等价，倘若第一根木棒就匹配失败，其它木棒也会失败


## 需要重复阅读理解，很经典的剪枝策略，尤其是维护单调性和从大到小排序此类套路性剪枝的理解记忆

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
int n,x,t;
int cnt,sum,val;
int v[105],s[105];

inline bool cmp(int a,int b){return a>b;}
inline bool dfs(int nbr,int len,int las){
	if(nbr>x) return true;
	if(len==t) return dfs(nbr+1,0,1);
	int fl=0;
	for(int i=las;i<=n;i++){
		if(!v[i]&&len+s[i]<=t&&fl!=s[i]){
			v[i]=1;
			if(dfs(nbr,len+s[i],i)) return true;
			v[i]=0,fl=s[i];
			if(len==0) return false;
		}
	}
	return false;
}

int main(){
	while(cin>>n&&n){
		sum=val=0;
		for(int i=1;i<=n;i++){
			cin>>s[i];
			sum+=s[i],val=max(val,s[i]);
		}
		sort(s+1,s+n+1,cmp);
		for(t=val;t<=sum;t++){
			if(sum%t) continue;
			x=sum/t;
			memset(v,0,sizeof(v));
			if(dfs(1,0,1)){
				cout<<t<<endl;
				break;
			}
		}
	}
	
	return 0;
}
```

---

## 作者：狸狸养的敏敏 (赞：17)

### 这就是一道DFS(大法师)
## 不要想多了
# 多想想剪枝！
附上题解，程序内有很详尽的注释(针对poj1011=UVA307的，当然也有针对luogu1120的代码，附在里面了)

~~顺便吐槽一下你谷的恶意评分现象太严重了~~

~~顶多蓝题怎么上紫的~~

```cpp
/*
POJ 1011 = UVA 307
**************************
木棒

Time Limit: 1000MS
Memory Limit: 10000K
Total Submissions: 156283
Accepted: 37378

Description
乔治拿来一组等长的木棒，将它们随机地砍断，使得每一节木棍的长度都不超过50个长度单位。
然后他又想把这些木棍恢复到为裁截前的状态，但忘记了初始时有多少木棒以及木棒的初始长度。
请你设计一个程序，帮助乔治计算木棒的可能最小长度。每一节木棍的长度都用大于零的整数表示。

Input
输入包含多组数据，每组数据包括两行。第一行是一个不超过64的整数，
表示砍断之后共有多少节木棍。第二行是截断以后，所得到的各节木棍的长度。

在最后一组数据之后，是一个零。
Output
为每组数据，分别输出原始木棒的可能最小长度，每组数据占一行。

Sample Input

9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0

Sample Output
6
5

**************************

luogu上的题目1120，可能会有长度>50的木棍存在，所以你们自己过滤下qwq
我就针对这道POJ上的题目写个题解

思路差不多嘛qwq
管理员不给过就熊你哈VwV
*/
#include<bits/stdc++.h>
using namespace std;
int n,lmark,ans,sum;
int nd;//当前枚举到的木棍长度
int a[66];//记录木棍长度
bool vis[66];//记录木棍有没有被用过
bool cmp(int x,int y) {//排序比较规则，将木棍从大到小排序
    return x>y;
}
bool dfs(int num,int len) {//num表示还有num根可以用,len表示还有len的长度就构造成1根完整的了
    if(num==0&&len==0)//如果木棍全部用完然后又构造好了木棍
        //由我们前面是计算除法，所以当num==0时，木棍的根数定然是最多的AwA
        return 1;
    if(len==0)len=nd;//构造完1根了，就再来一根
    int mark=1;//记录循环开始点
    if(len!=nd)mark=lmark+1;//如果不是一根全新的开始，就把mark（循环开始点）记为lmark+1(前面非重复木棍的位置)
    for(int i=mark; i<=n; i++)//剪枝，从前面非重复的位置开始循环 (枚举与当前木棍（已构成）进行匹配的木棍)
        if(vis[i]==0&&a[i]<=len) {//vis数组记录这个木棍有没有被用过
            if(i>1&&vis[i-1]==0&&a[i]==a[i-1])//剪枝；当出现重复木棍时，直接跳过
                //可以证明，在重复木棍中任取一根，不影响答案最终结果
                /*
                An example

                Input
                6
                1 1 1 2 2 2

                Output
                3

                可以见得，取第1根和取第2根和取第3根和后面的长度为2的木棍进行匹配，是不影响程序最终结果的
                重复的只计算第一根
                那么可以减少计算量
                由于我们已经排过序了
                那么判断重复就简单了
                */
                continue;
            vis[i]=1;//记为该木棒已经用过了
            lmark=i;//最后的不重复位置
            if(dfs(num-1,len-a[i]))//考虑下一根木棍
                return 1;
            else {
                vis[i]=0;//回溯
                if(len==a[i]||len==nd)
                    return 0;//len==a[i]说明当前木棍是被剩余的
                //len==nd是指当前木棍 无法被匹配（即上面的dfs(num-1,len-a[i])无法被触发）
                //那么当前答案肯定不是一种可行的方案
            }
        }
    return 0;
}
int main() {
    while(scanf("%d",&n),n) { //针对POJ的哦
        //如果是luogu上的1120话
        //应该介样子写
        //scanf("%d",&n);
        ans=sum=0;
        for(int i=1; i<=n; i++) {
            scanf("%d",a+i);
            sum+=a[i];//sum累计总长度，为后面的剪枝做好铺垫
        }//也是针对POJ的和蔼数据
        //对于luogu1120，你应该这样子写
        /*
            int cnt=n,n=0;
            for(int i=1;i<=cnt;i++)
            {
                int x;
                scanf("%d",&x);
                if(x<=50)a[++n]=x;
            }
        */
        sort(a+1,a+n+1,cmp);//排序，为去重做好铺垫
        for(int i=a[1]; i<=sum/2; i++) {//剪枝;每根木棍的长度只可能sum>=x>=min{a},且不可能在sum{a}/2-sum{a}之间
            //即若在sum{a}/2-sum{a} 之间时
            //定然会触发sun%i>0的条件
            //减少计算量qwq
            if(sum%i)continue;//剪枝；如果木棍的总长度无法整除当前枚举的长度
            //说明无论如何都无法构成完整的根
            memset(vis,0,sizeof(vis));//把标记数组清空
            lmark=1;
            nd=i;//记录下来枚举到的长度（我懒得开全局变量了2333）
            if(dfs(n,i)) {
                ans=i;
                break;//如果搜到了，因为我们是从小到大循环，如果找到了，那么这个解定然是最优解
                //直接记录下ans，就可以闪人了
            }
        }
        if(ans)printf("%d\n",ans);//如果ans有被更新过（即找到了比所有的凑成1根更好的答案），那么输出更好的答案
        else printf("%d\n",sum);//不然就把所有拼到一起
    }
    return 0;//完结撒fafa
}
```
~~其实蓝书（信息学奥赛一本通【提高篇】）上面有更多的剪枝~~

~~但是似乎有些剪枝奇奇怪怪~~

~~是错的呢qwq~~

好惹，就到这里啦。

---

## 作者：Azuree (赞：8)

[查看原题请戳这里](https://www.luogu.org/problem/UVA307)

注: 下文中`初始木棍`指答案所求木棍,`小木棍`指输入的木棍.

第一眼看到这个题,感觉就是个无脑搜索,然后......~~暴0快乐~~

具体搜索的思路就是枚举初始木棍的长度,然后直接搜索每根木棍是由哪些小木棍拼成的.

但是,这样搜索肯定会`TLE`,所以我们要~~稍稍~~进行一点剪枝:

1. 初始木棍长度大于等于最长的小木棍的长度,小于等于所有小木棍的总长,我们可以依次缩小枚举答案的范围.
2. 小木棍总长肯定是初始木棍长度的倍数,所以我们只在$sum / len = 0$时进行搜索.
3. 如果初始木棍长度到达$sum/2$时依然无解,这就说明即使把所有小木棍拼成两根时依然误解,于是我们可以直接让这些小木棍拼成一根,即如果当长度从$1$到$sum/2$枚举完一遍后依然无解,那么无须枚举$sum/2+1$到$sum$的部分,直接输出$sum$(即让所有木棍拼成一根)即可.
4. 较短的木棍应用起来比长的木棍运用灵活,即如果一根长木棍可以用几根短木棍拼成,那么如果这根长木棍长度合适,那么优先选长木棍表达这一长度一定不会劣于用那些小木棍拼成这个长度,所以我们可以将木棍从大到小排序后优先选取长的木棍进行拼接.
5. 如果我们将木棍从大到小排序以后,当我们在尝试拼第$k$根初始木棍时,可以记录上一次选取木棍$last$,然后在$last + 1$到$n$的范围内去枚举下一根木棍放什么(因为木棍$1$到$last$放或不放在之前肯定已经搜索过了).
6. 对于相同长度的木棍$a_i$,$a_j$,如果我们在第$k$根放$a_i$是发现无法拼成想要的长度,那么放$a_j$肯定也拼不出来你想要的长度,直接while循环弹掉即可(ps:暴力弹数在时间复杂度上没有问题,如果你想追求极致的速度体验,那么你可以通过二分来求下一个枚举的木棍或把相同长度的木棍压在一起并记录总量).
7. 如果当前要拼第$k$根原始木棍,而你现在还没有开始拼,那么我们本轮搜索可以强制选择当前可以选择的最长的木棍,因为当前我们还一根木棍都没有选,而这根最长的木棍迟早都要选,那么我们不如在这一轮直接选择它,这也体现了我们从大到小枚举的原则.如果我们选择这根木棍后最终无发拼出我们想要的等长的若干根木棍,那么如果选择先拼其他木棍也无法改变这个结果--也就是说,肯定是之前确定的方案出现了问题(不合法,最终无法构造成功),那么我们可以直接回溯到上一层继续搜索.
8. 如果加入当前枚举到的木棍以后直接可以拼出我们想要的长度$len$,那么根据优化$4$中所说的原因,直接加入它肯定是最优的,于是我们就不用考虑去拼其它的木棍了,因为如果选择最优方案都无法拼出答案,那么选择其它的方案就更不可能了.

code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register

using namespace std;

int read()
{
    register int x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}

int n,m,x,sum,len,tot,flag,a[1000005],vis[100005];

bool cmp(int a,int b){return a > b;}

void dfs(int k, int now, int las)
{
    if(flag) return ;
    if(now == len) now = 0, k++, las = 0;
    if(k > tot)
    {
        flag = 1;
        printf("%d\n",len);
        return ;
    }
    for(re int i = las + 1; i <= n; i++)
    {
        if(vis[i]) continue;
        if(now + a[i] <= len) vis[i] = 1,dfs(k,now + a[i],i),vis[i] = 0;
        if(now == 0 || now + a[i] == len) return ;
        while(a[i + 1] == a[i]) i++;
    }
}

int main()
{
    n = read();
    while(n)
    {
        sum = 0; m = 0; flag = 0;  //初始化点题
        for(re int i = 1; i <= n; i++)
        {
            x = read();
            if(x <= 50) a[++m] = x,sum += x;
        }
        sort(a + 1, a + n + 1, cmp);
        for(re int i = a[1]; i <= sum / 2; i++)
        {
            if(sum % i != 0) continue;
            memset(vis,0,sizeof(vis));
            tot = sum / i; len = i; flag = 0;
            dfs(1,0,0); 
            if(flag) break;
        }
        if(!flag) printf("%d\n",sum);
        n = read();
    }
    return 0;
}
```

---

## 作者：Stephzzz (赞：5)


采用深度优先搜索（$DFS$）算法.

搜索的对象就是原始木棍的长度，可以从小到大搜索，在搜索前，可以先计算所有小木棍的长度之和$S$，因为我们知道，所有小木棍都是由原始木棍截出来的，所以$S$一定是我们要搜索的**原始木棍长度L的整数倍**。这可以跳过很多无效的L！

对于每一个要搜索的L，我们要检查所有的小木棍是否能够拼回原木棍，在搜索之前，应该要从最长的小木棍开始搜索，也就是说**从大到小**开始搜索，这样我们才能够保证不重复，并且已拼成功的小木棍要在递归时标志为已使用，保证不重复以避免重复。

为了保证搜索时是从大到小搜索，我们应该对小木棍的长度进行排序（或有序保存），另外我们在搜索时，搜索函数需要知道当前搜索的原始木棍长度，当前已拼接的长度，当前准备拼接的小木棍需要，所以定义搜索函数$dfs$时需要三个参数。

一个比较强的剪枝是，如果当前能够拼出一条原始木棍，当前拼接的最后一段小木棍长度是t，但是剩余的其他小木棍无法全部拼接出原始小木棍，则不需要将t长度的小木棍替换为其他小木棍进行进一步的搜索，因为已经没有搜索的必要了。为什么呢？假设有解（即可以所有小木棍都可以拼接的话），那用$t$拼和用 $t1+…+ti=t$ 去拼是一样的，所以不可能有解。

在搜索过程中，我们可以通过一个变量来累计拼成功的小木棍的和，这样就可以通过该值判断是否与$S$相等判断是否找到解了。



---

## 作者：路人_ (赞：4)

# Sticks【题解】
其实，这题的难度很迷（我先在**POJ**上做的）；

至于为什么呢？

有一道数据加强版的难度是**提高+**

而原题（本题）是弱化的，难度确是**省选**      ~~（迷）~~

废话不多说，进入正题；


------------
其实这道题就是一个搜索，并且用上了剪枝。

### 划重点

所谓**剪枝**，就是减小搜索树的规模。尽早排除搜索树中不必要的分支的一种手段。**形象地看**，就好像剪掉了搜索树的枝条。

考虑以下剪枝：

**1.逆序搜索**

把木棍儿的长度从大到小排序；

**2.X+Y=Y+X(好理解吧）**

1）相同的只搜一遍；

2）如果现在已经拼成的长度，在后面是不可能成功的。那么我们就认定这个分支是失败的。所以如果之后的分支再次遇见像这样的长度。我们就直接把他给返回就可以了。

3）如果刚开始拼接木棒的时候，第一根已经导致了拼接失败。那我们就可以判定当前的大分支是不可行的。至于为什么，~~是因为他在第一次已经不行啦~~（开车）。那么它在其他木棒中也是不可以的。

其实大概的剪枝思想也就只这些；

下面上代码；


------------
**深搜代码**
```c
bool dfs(int now,int cab,int last)
//now表示现在在拼的第now根原始木棒
//cab表示第now根木棒的当前长度
//上一根小木棒是last
{
	if(now>s) return 1;//所有的木棒拼完了
	if(cab==l) return dfs(now+1,0,1);//l是拼完的长度，now根拼好了
	int f=0;//剪枝2，2）
	for(int i=last;i<=cnt;i++)//剪枝1
	{
		if(!k[i] && cab+a[i]<=l && f!=a[i])
		{
			k[i]=1;
			if(dfs(now,cab+a[i],i+1)) return 1;
			f=a[i];
			k[i]=0;//回溯
			if(cab==0 || cab+a[i]==l) return 0;//cab+a[i]==l加不加应该没影响
		}
	}
	return 0;//搜索失败
}
```



------------

**主函数**

```c
int main()
{
	int n;
	while(cin>>n&&n)//输入
	{
		memset(a,0,sizeof(a));//初始化
		memset(k,0,sizeof(k));
		cnt=0,v=0,sum=0,l,s;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			if(x>50) continue;//题意，防止毒瘤测试点
			a[++cnt]=x;
			v=max(v,x);
			sum+=x;
		}
		sort(a+1,a+cnt+1);
		reverse(a+1,a+cnt+1);//STL翻转数组
		for(l=v;l<=sum;l++)
		{
			if(sum%l) continue;
			s=sum/l;//原始木棒长l，共cnt根，故每根长sum/cnt；
			memset(k,0,sizeof(k));
			if(dfs(1,0,1)) break;
		}
		cout<<l<<endl;//输出答案
	}
	return 0;//完美结束
}
```

**完整代码**    ~~（拿走不谢）~~

```c
#include<bits/stdc++.h>
using namespace std;

int cnt=0,v=0,sum=0,l,s;
int a[100],k[100];

bool dfs(int now,int cab,int last)
{
	if(now>s) return 1;
	if(cab==l) return dfs(now+1,0,1);
	int f=0;
	for(int i=last;i<=cnt;i++)
	{
		if(!k[i] && cab+a[i]<=l && f!=a[i])
		{
			k[i]=1;
			if(dfs(now,cab+a[i],i+1)) return 1;
			f=a[i];
			k[i]=0;
			if(cab==0 || cab+a[i]==l) return 0;
		}
	}
	return 0;
}

int main()
{
	int n;
	while(cin>>n&&n)
	{
		memset(a,0,sizeof(a));
		memset(k,0,sizeof(k));
		cnt=0,v=0,sum=0,l,s;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			if(x>50) continue;
			a[++cnt]=x;
			v=max(v,x);
			sum+=x;
		}
		sort(a+1,a+cnt+1);
		reverse(a+1,a+cnt+1);
		for(l=v;l<=sum;l++)
		{
			if(sum%l) continue;
			s=sum/l;
			memset(k,0,sizeof(k));
			if(dfs(1,0,1)) break;
		}
		cout<<l<<endl;
	}
	return 0;
}
```
**求审过，（据说，考试前发题解会np++）**


第一篇**紫题**题解 ~~（太不容易了）~~，
最后**安利**下我的[博客](https://www.luogu.org/blog/lwhd/)








---

## 作者：happyZYM (赞：4)

做这题时我借鉴了某一大佬的博客：[传送门](https://www.luogu.org/blog/ogawa/solution-p1120)。
在这里我就把原文解释一下（详见代码）：
```cpp
#include<cstdio>
#include<cstring>
const int N=70;
int n,cnt,tot,maxn,minn,tm[N]; 
bool ok;
void dfs(int need,int sum,int goal,int maxlen)
{
	if(need==0)//找到了
	{
		printf("%d\n",goal);
		ok=true;
	}
	if(sum==goal)//拼完了一根 
	{
		dfs(need-1,0,goal,maxn);
		return;
	}
	for(int i=maxlen;i>=minn;i--)//用单调性确保不重复 
		if(tm[i]&&i+sum<=goal)
		{
			tm[i]--;
			dfs(need,sum+i,goal,i);
			if(ok) return;
			tm[i]++;
			if(sum==0||sum+i==goal) break;
            //如果刚好凑整的组合方式都不行，别的就更不行。
		}
}
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	while(scanf("%d",&n)==1&&n)
	{
		minn=N ;
		int x;
		cnt=tot=maxn=0;
		memset(tm,0,sizeof(tm));
		while(n--)
		{
			scanf("%d",&x);
			if(x<=50)
			{
				cnt++;
				tm[x]++;//用桶更方便 
				tot+=x;
				maxn=maxn>x?maxn:x;
				minn=minn<x?minn:x;
			}
		}
		x=tot/2;//tot一定可以，能算不举
		ok=false;
		for(int i=maxn;i<=x;i++)
			if(tot%i==0)
			{
				dfs(tot/i,0,i,maxn);
				if(ok) break;
			}
		if(!ok) printf("%d\n",tot);
	}
	return 0;
}
```

---

## 作者：Celtic (赞：3)

~~首先一看就是迭代加深搜索。~~

需要用到最优性剪枝和可行性剪枝。

从最优性方面分析，可以做以下两种剪枝：

1. 设所有木棍的长度和是$sum$，那么原长度（也就是需要输出的长度）一定能够被$sum$整除，不然就没法拼了，即一定要拼出整数根。

1. 木棍原来的长度一定大于等于所有木棍中最长的那根。

综合上述两点，可以确定原木棍的长度$len$在最长木棍的长度与$sum$之间，且$sum$能被$len$整除。所以，在搜索原木棍的长度时，可以设定为从截断后所有木棍中最长的长度开始，每次增加长度后，必须能整除$sum$。这样可以有效地优化程序。

从可行性方面分析，可以再做以下七种剪枝：

1. 一根长木棍肯定比几根短木棍拼成同样长度的用处小，即短小的可以更灵活组合，所以可以对输入的所有木棍按长度从大到小排序。

1. 在截断后的排好序的木棍中，当用木棍i拼合原始木棍时，可以从第$i+1$后的木棍开始搜。因为根据优化$(1)$，$i$前面的木棍已经用过了。

1. 用当前最长长度的木棍开始搜，如果拼不出当前设定的原木棍长度$len$，则直接返回，换一个原始木棍长度$len$。

1. 相同长度的木棍不要搜索多次。用当前长度的木棍搜下去得不出结果时，用一支同样长度的还是得不到结果，所以，可以提前返回。

1. 判断搜到的几根木棍组成的长度是否大于原始长度$len$，如果大于，没必要搜下去，可以提前返回。

1. 判断当前剩下的木棍根数是否够拼成木棍，如果不够，肯定拼合不成功，直接返回。

1. 找到结果后，在能返回的地方马上返回到上一层的递归处。


北京第三区交通委提醒您：**数据千万条，清空第一条。
多测不清空，爆零两行泪。**

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define eps 1e-10
#define re register
#define N 5001001
#define MAX 2001
#define PI acos(-1)
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	ret=pd?-ret:ret;
}
ll n,a[N],k,all,nxt[N];
bool vis[N];
inline bool dfs(re ll deep,re ll now,re ll las)
{
	bool flag=false;
	now%=k;
	
	if(!now)
	{
		if(deep>n)
			return true;
		for(re int i=1;i<=n;i++)
		{
//			cout<<i<<endl;
			if(!vis[i])
			{
		//		cout<<i<<endl;
				vis[i]=true;
				flag+=dfs(deep+1,now+a[i],i);
				vis[i]=false;
				if(flag)return true;
				return false;
			}
		}
	}
	re ll l=las+1,r=n,mid,tmp;
	while(l<r)
	{
		mid=l+r>>1;
		if(a[mid]+now<=k)
			r=mid,tmp=mid;
		else
			l=mid+1;
	}
	for(re int i=l;i<=n;i++)
	{
		if(vis[i])continue;
		vis[i]=true;
		flag+=dfs(deep+1,now+a[i],i);
		vis[i]=false;
		if(flag)return true;
		if(a[i]+now==k||!now)
			return false;
		i=nxt[i];
	}
	return false;
}
inline bool cmp(re ll x,re ll y)
{
	return x>y;
}
int main()
{
	all=0;
	read(n);
	if(!n)
		exit(0);
	for(re int i=1;i<=n;i++)
	{
		read(a[i]);
		if(a[i]>50)
			a[i]=0;
		all+=a[i];
	}
	sort(a+1,a+n+1,cmp);
	
	for(re int i=1;i<=n;i++)
	{
		if(a[i]&&!a[i+1])
		{
			n=i;
			break;
		}
	}
//	cout<<n<<endl;
	nxt[n]=n;
	for(re int i=n-1;i;i--)
	{
		if(a[i]==a[i+1])
			nxt[i]=nxt[i+1];
		else
			nxt[i]=i;
	}
	for(k=a[1];k<=all/2;k++)
	{
		if(all%k)continue;
		vis[1]=true;
		if(dfs(2,a[1],1))
		{
			vis[1]=false;
			printf("%lld\n",k);
			main();
		}
	}
	printf("%lld\n",all);
	main();
    exit(0);
}

```



---

## 作者：神之殇 (赞：3)

## 这道题就是一道**经典的搜索剪枝**题! 
### 剪枝优化三原则
1. **正确性**: 枝条不是爱剪就能剪的. 如果随便剪枝,把带有最优解的那一分支也剪掉了的话, 剪枝也就失去了意义。所以,剪枝的前提是一定要保证不丢失正确的结果。

2. **准确性**: 在保证了正确性的基础上, 我们应该根据具体问题具体分析, 采用合适的判断手段, 使不包含最优解的枝条尽可能多的被剪去,以达到程序“最优化”的目的。可以说, 剪枝的准确性, 是衡量一个优化算法好坏的标准。

3. **高效性**: 设计优化程序的根本目的, 是要减少搜索的次数, 使程序运行的时间减少. 但为了使搜索次数尽可能的减少, 我们又必须花工夫设计出一个准确性较高的优化算法, 而当算法的准确性升高, 其判断的次数必定增多, 从而又导致耗时的增多, 这便引出了矛盾。因此, 如何在优化与效率之间寻找一个平衡点, 使得程序的时间复杂度尽可能降低,同样是非常重要的. 倘若一个剪枝的判断效果非常好, 但是它却需要耗费大量的时间来判断、比较, 结果整个程序运行起来也跟没有优化过的没什么区别, 这样就太得不偿失了。


------------


### 深度优先搜索的优化技巧
1. **优化搜索顺序**：在一些搜索问题中，搜索树的各个层次，各个分支之间的顺序是不固定的。不同的搜索顺序会产生不同的搜索树形态，其规模大小也相差甚远。

2. **排除等效冗余**：在搜索过程中，如果我们能够判定从搜索树的当前节点上沿着某几条不同分支到达的子树是等效的，那么只需要对其中的一条分支执行搜索。

3. **可行性剪枝（上下界剪枝）**：该方法判断继续搜索能否得出答案，如果不能直接回溯。 在搜索过程中，即使对当前状态进行检查，如果发现分支已经无法到达递归边界，就执行回溯。

4. **最优性剪枝**：最优性剪枝，是一种重要的搜索剪枝策略。它记录当前得到的最优值，如果当前结点已经无法产生比当前最优解更优的解时，可以提前回溯。

5. **记忆化**：可以记录每个状态的搜索结果，再重复遍历一个状态时直接检索并返回。这好比我们对图进行深度优先遍历时，标记一个节点是否已经被访问过。


------------
这道题可以运用**最优性剪枝，可行性剪枝**来做，代码如下：
 
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int a[105],used[105],n,len,m,mmin=0,sum=0,bj;
bool cmp(const int &x,const int &y)
{
	return x>y;
}
void dfs(int k,int last,int rest)//第k跟木棍，last为上一节木棍编号，rest为第k根木棍还需要的长度 
{
	int i,j;
	if(k==m)// 剪枝9 
	{
		bj=1;
		return;
	}
	if(rest==0)
	{
		for(i=1;i<=n;i++)//剪枝4 
		{
			if(!used[i])
			{
				used[i]=1;break;
			}
		}
		dfs(k+1,i,len-a[i]);
	}
	for(i=last+1;i<=n;i++)//剪枝5和7 
	{
		if(!used[i]&& rest>=a[i])
		{
			used[i]=1; //当前木棍已使用 
			dfs(k,i,rest-a[i]);
			used[i]=0; 
			j=i;
			while(i<n && a[i]==a[j])i++;//剪枝6 
			if(i==n)
			{
				return;
			}
		}
	}
}
void solve()
{
	int i,j;
	for(i=mmin;i<=sum;i++)//剪枝2 
	{
		if(sum%i==0)//剪枝1 
		{
			memset(used,0,sizeof(used));
			len=i;
			used[1]=1;
			bj=0;
			m=sum/i;//木棍的根数 
			dfs(1,1,len-a[1]);
			if(bj)
			{
				cout<<len<<endl;
				break;
			}
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		mmin=max(mmin,a[i]);
		sum=sum+a[i];
	}
	sort(a+1,a+1+n,cmp);
	solve();
	return 0;
}
/*
9
5 2 1 5 2 1 5 2 1
*/
```
### 分析：
**最优性剪枝：**

1 、设所有木棍的长度和为sum ，原长度一定能被sum 整除；

2 、木棍原始长度一定不小于所有木棍中最长的那个；

**可行性剪枝：**

3 、长木棍肯定比几根短木棍拼成同样长度的用处小，短木棍
； 更灵活，可以对木棍从大到小排序；

4 、当用木棍i 拼凑原始木棍时，可以从第i+1 后的木棍开始搜，
化 因为根据优化1 ，i 前面的木棍已经用过了；

5 、用当前最长长度的木棍开始搜，如果拼不出当前设定的圆
度 木棍长度len ，则直接返回，换一个原始木棍长度len ；

6 、相同长度的木棍不要搜索多次。用当前长度的木棍得不出
； 结果是，用同一支长度相同的还是得不到结果，可以提前返回；

7 、判断收到的几根木棍组成的长度是否大于原始长度len ，如
； 果大于，可以提前返回；

8 、判断当前省的木棍根数是否够拼成木棍，如果不够，直接
； 返回；
9 、找到结果后，在能返回的地方法返回到上一层的递归处。


---

## 作者：Partial (赞：2)

总之是一个比较恶心的题。
直接写下来剪枝吧

 - 优化搜索顺序：从最大开始枚举，枚举棍棍长度应是总长度的公因数，从使用过的木棍往后枚
 - 排除等效冗余：用过的木棍失败的记录长度如果相同就false，如果当前的棍长=0或加上当前棍子是len还错了就false
 
 代码如下：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=65;
int n,m,a[N],num,cnt,len,vis[N];
bool cmp(int a,int b)
{
	return a>b;
}
bool dfs(int c,int b,int t)
{
	if(c==cnt)return true;
	if(b==len)return dfs(c+1,0,1);
	int fail=0;
	for(int i=t;i<=num;++i)
	{
		if(!vis[i]&&a[i]+b<=len&&a[i]!=fail)
		{
			vis[i]=1;
			if(dfs(c,b+a[i],i+1))return true;
			fail=a[i];
			vis[i]=0;
			if(b==0||b+a[i]==len)return false;
		}
	}
	return false;
}
int main()
{
	while(cin>>n&&n)
	{
		m=0,num=0;
		for(int i=1,x;i<=n;++i){
			cin>>x;if(x>50)continue;
			a[++num]=x;m+=x;
		}
		sort(a+1,a+num+1,cmp);
		for(len=a[1];len<=m;++len){
			if(m%len!=0)continue;
			cnt=m/len;
			memset(vis,0,sizeof(vis));
			if(dfs(0,0,1))break;
		}
		cout<<len<<endl;
	}
	return 0;
} 
```

 
 


---

## 作者：EarringYYR (赞：1)

为了更好的阅读体验，请移步我的博客：[http://www.earringyyr.com/2018/12/23/uva307-【小木棍-sticks】题解](http://www.earringyyr.com/2018/12/23/uva307-【小木棍-sticks】题解)

这道题总体来说还是非常简单的，就是搜索+剪枝。

搜索怎么搜应该没什么好讲的。

以下为几个剪枝思路：

1. 枚举原始木棒的长度时，最小值显然应该为所有小木棍的最大值。最大值显然应该是所有木棍的长度综合，但我们并不需要这么做。我们只需要枚举到所有木棍的长度总和的二分之一，加入这样都没有解决方案，那么答案就显然是所有木棍的长度的总和。

2. 对于长度大于50的木棍直接忽略（不符合要求）

3. 将所有输入的木棍按长度从大到小排序（这个可以感性理解）

4. 每次DFS时，如果当前长度进行搜索时不行，那么可以直接跳过和他长度相等的木棒（因为在当前状态不变的情况下liu）

5. 若当前木棒的长度等于当前在拼的木棒的剩余长度且情况不可行时，那么直接回溯（因为加入继续搜下去也不过是用后面的几根木棒组成了当前木棒的长度，浪费了更多资源，留给后面的选择也更少了，显然不是最优解）。

6. 若当前在拼的木棒长度等于期望的原始长度，那么直接回溯（类似于上米娜两种情况，继续搜下去不仅状态不会改变，反而状态变少了，显然不是最优解）。

有了以上这么多的剪枝的支持，这道题就完成了。

下面给出完整代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int nn, n, cnt, ma, mi, ans, num, a[70], use[70], pan;
inline void dfs(int sum, int k, int last)
{
    if (sum == ans)
    {
        cout << num << endl;//因为搜索的顺序是从小到大的，所以第一个搜到的必定是最小的
        pan = 1;
        return;
    }
    if (k == 0)
    {
        dfs(sum + 1, num, 0);
        return;
    }
    if (k < mi)
        return;
    for (register int i = last + 1; i <= n; ++i)
    {
        if (use[i] == 0 && k >= a[i])
        {
            use[i] = 1;
            dfs(sum, k - a[i], i);
            use[i] = 0;
            if (pan == 1)
                return;
            while (a[i + 1] == a[i])
                ++i;
            if (k == num || k == a[i])
                return;
        }
    }
    return;
}
bool cmp(int aa, int bb)
{
    return aa > bb;
}
int main()
{
    while (cin >> nn)
    {
        if (nn == 0)
            return 0;
        pan = 0;
        n = 0;
        cnt = 0;
        ma = 0;
        mi = 0x3f3f3f;
        ans = 0;
        num = 0;
        memset(use, 0, sizeof(use));
        for (register int i = 1; i <= nn; ++i)
        {
            int lin;
            cin >> lin;
            if (lin <= 50)
            {
                a[++n] = lin;
                cnt += a[n];
                ma = max(ma, a[n]);
                mi = min(mi, a[n]);
            }
        }
        sort(a + 1, a + n + 1, cmp);
        for (register int j = ma; j <= cnt / 2; ++j)
            if (cnt % j == 0)
            {
                num = j;
                ans = cnt / j;
                dfs(0, num, 0);
                if (pan == 1)
                    break;
            }
        if (pan == 0)
            cout << cnt << endl;
    }
    return 0;
}
```

---

## 作者：Lube (赞：0)

## 这一题的本质，简而言之就是暴力搜索。但是俗话说得好，DFS天生具有某种 _低调而又奢华的气质_ ……所以，介于本题的数据量，我们必须对纯暴力的DFS进行一些优化，即剪枝。本题的最特殊之处，也可以说是最大的难点，就在于利用一切的剪枝方法进行时间复杂度的优化。在这里，我给出了5种优化的手段。具体方法如下：
```
#include<bits/stdc++.h>
using namespace std;
int wood[70],tot,tt,sum,ys[1005],n,lenmax,fail;
bool use[1005],tf;
bool cmp(int a,int b){return a>b;}
void dfs(int lennow,int num,int lensum)
//lennow:当前正在拼接的木棍拼了多长
//num：从第几根断木棍开始选择（详情见优化2）
//lensum：选取的所有木棍的总长度。功能类似于标记拼好了几根完整的木棍 
{
    if(lennow==lenmax)//有一根木棍已经拼好了。但是此时有两种可能如下 
    {
        if(lensum==sum){printf("%d\n",lenmax);tf=1;return;}
        //第一种可能：所有的木棍全都拼好了，于是将标记变量tf标记为1，输出，回溯。 
        lennow=0;num=1;
        //第二种可能 ：还有的木棍没开始拼，于是开始下一根木棍的拼接。注意初始化。 
    }
    fail=0;
    for(int i=num;i<=tot;i++)
    //优化2：我们先前已经对断木棍进行了排序。在此，我们限定，在拼接合法的前提下，尽可能拣最长的木棍拼上，并严格的使木棍从长到短的拼接。因为两根木棍，先拼短后拼长，与先拼长后拼短，二者等效。之所以先拼长的，详见主函数中sort处的注释 
    {
        if(lennow+wood[i]<=lenmax&&!use[i]&&fail!=wood[i])
        //若拼接合法（长度没有超过限度，此根木棍也未使用。fail作用见下面的） 
        {
            use[i]=true;
            dfs(lennow+wood[i],i+1,lensum+wood[i]);
            //选定了第i根木棍拼上。
            if(tf==1)return;//如果所有的木棍都拼接成功，直接回溯 
            use[i]=false;
            fail=wood[i];
            //优化3：若递归回溯至此，说明本分支搜索失败。即如果在这个位置拼接了第i根木棍，无论之后如何拼接，都无法成功拼完所有木棍。同样的，与第i根木棍长度相等的木棍，若拼接在此处，同样无法成功，故在此剪枝。 
            if(lennow==0||lennow+wood[i]==lenmax)return;
            //优化4：若在第i根木棍拼接前，所有的待拼接木棍长度都为0，且第i根木棍最终拼接失败，则所有的长度为0的待拼接木棍，只要第一根木棍长度等于此根木棍，则一定失败
            //优化5：若待拼接木棍接上第i根木棍后正好拼成完整的木棍，但之后的拼接失败，说明即使这根木棍能成功拼接，但无论之后采取什么方法，剩下的木棍一定无法成功拼接完 
        }
    }
}
int main()
{
    scanf("%d",&n);
    while(n!=0)//这个不用解释了吧？只要输入的不是0，就一次一次循环输入 
    {
        memset(wood,0,sizeof(wood));
        memset(use,0,sizeof(use));
        memset(ys,0,sizeof(ys));
        tot=0;tt=0;sum=0;lenmax=0;fail=0;tf=0;//千万别忘了把上次运行完的变量清零，否则会乱 
        for(int i=1;i<=n;i++)
        {
            int leen;scanf("%d",&leen);if(leen<=50){tot++;wood[tot]=leen;sum+=leen;}
        }//自动过滤掉大于50长度的木棍 
        sort(wood+1,wood+tot+1,cmp);//改变搜索顺序，优先考虑拼上较长的木棍。这样，待拼接的木棍剩下的空间就小了，即距此根木棍拼满还需要拼接的木棍数就更少了，从而减小搜索树规模。 
        for(int i=1;i<=sum;i++)
        {
            if(sum%i==0&&i>=wood[1]){tt++;ys[tt]=i;}
        }//优化1。先前用sum算出了所有合法断木棍的总长。那么原先完整的木棍的长度只可能是sum的因数，并且长度要大于等于断木棍中最长的一根。 
        for(int i=1;i<=tt;i++)
        {
            lenmax=ys[i];//枚举完整木棍的长度 
            dfs(0,1,0);//开始搜索 
        }
        scanf("%d",&n);
    }
}
```


---

## 作者：wyhwyh (赞：0)

## UPD:去掉了一些与本题无关的内容。

这题主要有5个剪枝。具体结合代码分析一下（代码在下面）

我们约定"木棍"能拼成"木棒"。

1. 代码第41行：先把木棒长度排序，至于这样为什么是对的，就是说如果能用多根短木棍拼成一根长木棒的长度等于一根长木棍的长度，那直接用这根长木棍肯定更优对吧，这种感觉。。。

2. 第42行：枚举木棒长度时，从最长木棍长度枚举到所有木棍的总长度。而且遇到不能整除的跳过。这肯定也是对的对吧qwq。因为最长木棍长度就是单独成为一根木棒。而所有木棍的总长度就是所有的木棍拼成一根木棒。

3. 第29行：在dfs中返回时直接将vis清0.这样就可以省了第44行的memset，大大节约了时间。

4. 第31行：如果一根木棒当前是“新的”，并且拼第一根木棍的时候就失败了，那么也不用试其他的了，因为当前这根木棍肯定用不上了啊，直接回溯。

5. 第32行：如果一根木棒加上当前木棒的长度就等于总长度，并且当前长度失败了的话，那么就可以直接回溯了。

**Code**

```cpp

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 100;
int n,maxnum,maxlen;//maxnum means how many sticks will be at last. 
int a[N],vis[N];

bool cmp(int x,int y)
{
	return x>y;
}

int dfs(int num,int len,int last)
//now means how many sticks is have been done 
//len means the length of the STICK 
{
	if(len>maxlen) return 0;//cannot 
	if(num>maxnum) return 1;//done 
	if(len==maxlen) return dfs(num+1,0,1);//done this one and start next one 

	for(int i=last;i<=n;++i)
	{
		if(vis[i]) continue;
		vis[i]=1;
		if(dfs(num,len+a[i],i)) {vis[i]=0;return 1;}
		vis[i]=0;
		if(len==0) return 0;
		if(len+a[i]==maxlen) return 0;
	}
	return 0;//searching failed 
}

void work()
{
	int all=0,maxx=0;
	for(int i=1;i<=n;++i) {scanf("%d",&a[i]);all+=a[i];maxx=max(maxx,a[i]);}
	sort(a+1,a+n+1,cmp);
	for(int i=maxx;i<=all;++i)
	{
//		memset(vis,0,sizeof vis);
//		这里如果用memset就会T的飞起emmmm 
		if(all%i) continue;
		maxnum=all/i;maxlen=i;
		if(dfs(1,0,1))
		{printf("%d\n",maxlen);return;}
	}
}

int main()
{
	scanf("%d",&n);
	while(n)
	{
		work();
		scanf("%d",&n);
	}
	return 0;
}

//UPD:那个“STICK”指的是用几根短木棍拼成的长木棒。 

```


---

