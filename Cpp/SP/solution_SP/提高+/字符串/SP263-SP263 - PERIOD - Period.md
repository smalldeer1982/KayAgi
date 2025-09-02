# SP263 - PERIOD - Period

## 题目描述

如果一个字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，则称 $T$ 是 $S$ 的循环元。使 $K$ 最大的字符串 $T$ 称为 $S$ 的最小循环元，此时的 $K$ 称为最大循环次数。

现给一个给定长度为 $N$ 的字符串 $S$，对 $S$ 的每一个前缀 $S[1\sim i]$，如果它的最大循环次数大于 $1$，则输出该前缀的长度和最大循环次数。

## 说明/提示

Translate by [@qifan_maker](/user/706607).

## 样例 #1

### 输入

```
2
3
aaa
12
aabaabaabaab```

### 输出

```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4```

# 题解

## 作者：辰星凌 (赞：56)

# 在进入这道题之前，我们先来学习一下 kmp 算法
（~~如果大佬您已经学习过了，可以直接跳到后面周期性的解释~~）
## 术语与规定

为了待会方便，所以不得不做一些看起来很拖沓的术语，但这些规定能让我们更好地理解$KMP$甚至$AC$自动机。

**字符串匹配**形式化定义如下：
假设文本是一个长度为$n$的数组$T[1...n]$，而模式是一个长度为$m$的数组$P[1...m]$，其中$m<=n$，进一步假设构成$P$和$T$的元素都是来自一个有限字母集$\Sigma$的字符。例如：$\Sigma=${$0,1$}或者$\Sigma=${$a,b,...,z$}。字符数组通常称为字符串。

我们用$\Sigma^*$表示所有有限长度字符串的集合，该字符串由字母表$\Sigma$中的字符组成。特别地，长度为$0$的空字符用$\varepsilon$表示，也属于$\Sigma^*$。一个字符串$x$的长度用$|x|$表示。两个字符串$x$和$y$的**连结**用$xy$来表示，长度为$|x|+|y|$，由$x$的字符串后接$y$的字符串构成。


![图一](https://i.loli.net/2019/03/18/5c8eedcec4476.png)


如果$0<=s<=n-m$，并且$T[s+1...s+m]=P[1...m]$（即如果$T[s+j]=P[j]$，其中$1<=j<=m$），那么称模式$P$在文本$T$中出现，且偏移为$s$。如果$P$在$T$中以偏移$s$存在，那么称$s$是有效偏移；否则，称它为无效偏移。如图一，$s=3$就是一个有效位移。根据此约定，字符串匹配问题就可以变成：**对于模式串$P$找出所有文本串$T$的有效偏移**。

如果对于某个字符串$y\in\Sigma^*$有$x=wy$，则称字符串$w$是字符串$x$的**前缀**，记作$w\sqsubset x$。类似的，我们也可以定义后缀符号：若$x=yw$，则称字符串$w$是字符串$x$的**后缀**，记作$w\sqsupset x$。可以看出：如果$w\sqsubset x$，则$|w|<=|x|$。特别地，空字符串$\varepsilon$同时是任何一个字符串的前缀和后缀。

（想一想我们为什么要引入$\sqsupset$和$\sqsubset$符号。）

如果不做特殊说明，我们约定认为$a$为一个字符，即长度为$1$的字符串。

为了使符号简洁，我们把模式$P$的由前$k$个字符组成的前缀$P[1...k]$记作$P_k$，$P_m=P$，采用这种记号，我们又能够把字符串匹配问题表述成：
找到所有偏移$s(0<=s<=n-m)$，使得$P\sqsupset T_{s+m}$。



## 首先，我们考虑朴素算法的操作过程


![图二](https://i.loli.net/2019/03/18/5c8eee406dff1.png)


图一展示了一个针对文本串$T$模式串$P$的的一个特定位移$s$。它已经匹配到了$P_q$，在$q+1$的位置与文本串$T$**失配**。

按照朴素算法的操作，我们这时应进行$s'=s+1，q=1$的操作，把文本串的匹配指针左移到$s'+1$位，模式串$P$匹配指针移回$1$位，从头开始匹配。可这样时间开销是个很大的问题。

那怎么办呢？

我们能不能不把文本串的指针向左移，而直接把模式串的匹配指针对准下一个可能的匹配位置上，即只移动模式串$P$呢？

答案是可以的。

别忘了我们已经匹配好了$P_q$，这意味着我们已经知道了$T[s+1...s+q]=P[1...q]$，如果能把这东西给利用起来那该多好啊！

怎么用呢？

于是，$KMP$算法就来了。

## KMP主体

还是用图二。

![图二](https://i.loli.net/2019/03/18/5c8eee406dff1.png)

$q=5$个字符已经匹配成功的信息确定了相应的文本字符。已知的这$p$个文本字符使我们能够立即确认某些偏移一定是无效的。就比如上面所说的$s'=s+1$。


KMP算法思想便是利用已经匹配上的字符信息，使得模式串的指针回退的字符位置能将主串与模式串已经匹配上的字符结构**重新对齐**。

什么意思？

假设我们存在这样一个映射函数，先把它理解成一个小黑盒。当我们在模式串$q+1$的位置上失配时，它能跳到$P$串的某一位置$k$（注意是$P$串），即$k=next[q]$使得$P_{k}$与先前已匹配的$q$个字符的文本串不发生冲突，然后再比较$k+1$的位置是否与当前文本串指针匹配，如果不能，那继续找$next[k]$；如果能，那就成功匹配一位，进行下一位的匹配。这样，**文本串的指针只会向右移而不会向左移**。那么这个匹配程序就很好实现了。

这里直接给出伪代码：

```cpp
KMP-MATCHER(T,P)
  n = T.length
  m = P.length
  next = COMPUTE-PREFIX-FUNCTION(P)//这里的next就是那个小黑盒
  q = 0
  for i=1 to n
    while q>0 and P[q+1]!=T[i]
      q = next[q]
    if P[q+1] == T[i]
      q = q+1
    if q == m
      print "Pattern occurs with shift" i-m
      q = next[q]//匹配成功后肯定要往回走啊
```

这就是$KMP$算法的主体！

（仔细回味下）

 那我们怎么求这个$next[q]$呢？

我们来观察它的性质。


![图三](https://i.loli.net/2019/03/18/5c8eee5831888.png)


![图四](https://i.loli.net/2019/03/18/5c8eee5226fe2.png)


如图三，根据$q=5$个字符已经完全匹配，那么图中的$P_k\sqsupset T[s+1...s+q]$，且$k$是满足此条件的最大值，我们直接可以从$P[k+1]$开始与文本串匹配。也就是说，这里的$k$就是我们要找的$next[q]$。
在图四中，我们把$P_q$和$P_k$单独拿了出来，你发现了什么？

$P_k\sqsupset P_q$！

可以看出$k$是满足条件的最大值，也就是说：

$next[q]=max$ { $k:k<q$且$P_k$ $\sqsupset$ $P_q$ }


为什么会是这样呢？

我们想要直接在$k+1$位开始匹配，就得保证$P_k\sqsupset T[s+1...s+q]$，虽然我们在$q+1$位失配，但我们已经知道了$P_q = T[s+1...s+q]$，所以即有$P_k\sqsupset P_q$。

那为什么我们会要求$k$为满足条件的最大值呢？
这里先简单理解，**$k$为最大值也就包含了$k$为更小值的情况**。

那么，这个$next$我们就把它视为$P$的**前缀函数**。

那么，怎么来求这个$next$呢？

首先，我们肯定能想到一种朴素算法，这里就不细说了，因为用朴素算法还不如敲个$O((n-m+1)m)$的匹配算法呢。。。

那我们怎么来优化求法呢？

同样假设，对于一个模式串$P$，我们已经知道了$next[1...q-1]$，现在，我们来计算$next[q]$。其中，$next[q-1]=k$。

## 引理1：当$P[k+1]=P[q]$时，可得$next[q]=k+1$。（前缀函数延续性引理）

证明：
因为：$next[q-1]=k$ 即 $P_k\sqsupset P_{q-1}$。
若字符$P[k+1]=P[q]$，则$P_{k+1}\sqsupset P_q$。
所以：$next[q]=k+1$。
证毕。

## 引理2：若$next[q-1]$的最大候选项为$k$，即$next[q-1]=k$，则它的次大候选项为$next[k]$，次次大为$next[next[k]]$......（前缀函数迭代引理）
证明：（反证法）
若存在$k_0$使得$P_{k_0}\sqsupset P_{q-1}$且$next[k]<k_0<k$。
因为：$next[q-1]=k$，即$P_k\sqsupset P_{q-1}$。
又因为：$k_0<k$。
所以：$P_{k_0}\sqsupset P_k$。
即：$next[k]=k_0$。
这与$next[k]<k_0$矛盾。
所以假设不成立。
证毕。
后面的依次类推。

由前两个引理可以看出，$next[q]$可能的候选项为：$next[q-1]+1$，$next[next[q-1]]+1$......而易知，$next[1]=0$。


![图五：模式串P为ababaca时的前缀函数的值](https://i.loli.net/2019/03/18/5c8eef84c2578.png)


于是，我们便可以高效计算$next$数组。

```cpp
COMPUTE-PREFIX-FUNCTION(P)
  m = P.length
  pi[1] = 0
  k = 0
  for q=2 to m
    while k>0 and P[k+1]!=P[q]
      k = pi[k]
    if P[k+1] == P[q]
      k = k+1
      pi[q] = k
```

是不是和$KMP-MATCHER$很像？

其实，实质上，**KMP算法求前缀函数的过程就是模式串的自我匹配**。

为什么我们先说$KMP$算法的主体再谈$next$的计算？其实这是从两种角度出发认识$KMP$。讲解主体的时候我们采用了假设法，这是一种十分感性的认知，比较好懂。在讲解$next$的计算时，我们引用了一些数学思维来帮助我们更加理解$KMP$。大家可以看出，实质上，$KMP$主体和$next$的计算是几乎一样的逻辑。

#### 至此，$KMP$算法原理的讲解到此结束。
-----------

## 参考文献
- 算法导论
- 算法进阶指南
- [详解KMP](https://www.cnblogs.com/yjiyjige/p/3263858.html)
- [剖析KMP](https://blog.csdn.net/v_july_v/article/details/7041827)
- [字符串匹配算法集合](https://blog.csdn.net/force_eagle/article/details/10340729)


------------

##### 附：以上文字均来自[Silent_EAG —— ~~一个可爱的女孩纸~~](https://www.luogu.org/space/show?uid=111674) [她的博客](http://www.cnblogs.com/silentEAG/)

------------

## 关于 kmp 算法中 next 数组的周期性质

### 引理：

对于某一字符串 $S[1$～$i ]$，在它众多的$ next[ i ] $的“候选项”中，如果存在某一个$ next[ i ] $，使得: $i$ % $( i - next[ i ] ) == 0$ ，那么 $S[ 1$～ $( i -next[ i ] ) ]$ 可以为 $S[ 1$ ～ $i ]$ 的循环元而 $i / ( i - next[ i ] )$ 即是它的循环次数 $K$。

### 证明如下：


![](https://i.loli.net/2019/03/18/5c8ef2d7949af.png)


如图，$next[ i ] = j$,由定义得红色部分两个子串完全相同。  
那么有$S[ 1$～$j ] = S[ m$～$i ]$ $( m = i - next[ i ] )$。



------------


![](https://i.loli.net/2019/03/18/5c8ef2d78cfbb.png)


如果我们在两个子串的前面框选一个长度为 m 的小子串(橙色部分)。

可以得到：$S[ 1$～$m ] = S[ m$～$b ]$。

------------

![](https://i.loli.net/2019/03/18/5c8ef2d8461dd.png)


如果在紧挨着之前框选的子串后面再框选一个长度为 m 的小子串(绿色部分)，同样的道理，

可以得到：$S[ m$～$b ] = S[ b$～$c ]$   
又因为：$S[ 1$～$m ] = S[ m$～$b ]$  
所以：$S[ 1$～$m ] = S[ m$～$b ] = S[ b$～$c ]$

-------------


![](https://i.loli.net/2019/03/18/5c8ef2df2845d.png)

如果一直这样框选下去，无限推进，总会有一个尽头。  
当满足 $i$ % $m == 0$ 时，刚好可以分出 $K$ 个这样的小子串，
且形成循环$( K = i / m )$。

-------------

因此我们需要从 $1$～$N$ 扫一遍，判断如果 $next[ i ]$ 
    可以整除 $i$ ，即满足 $i$ % $( i - next[ ] ) == 0$ ，那么就可以
    肯定$S[ 1$～ $( i - next[ i ] ) ]$是 $S[ 1$～$i ]$ 的最小循环元，而
     $i / ( i - next[ i ] )$ 即是它的最大循环次数 $K$ ，直接依次输
    出这些 $i$和 $K$ 即可。

-------------

那么为什么只判断 $next[ i ]$ 而不判断 $next[?]$呢？  
（注：$next[i]$和$next[?]$表述的意义不同，为方便描
   述，这里定义$next[?]$为$next[i]$的$“候选项”中的某一个）
   
   
### 实际上由这道题可以总结出很多结论：


#### 结论一：

若$i-next[i]$可整除$i$,则$s[1$～$i]$具有长度为$i-next[i]$
        的循环元，即$s[1$～$i-next[i]]$。(前面的~~一大堆~~文
        字和图片已经给出了这个结论的证明，同时结论一
        也是后面推导其他结论的理论基础）

#### 结论二：

若$i-next[?]$可整除$i$,则$s[1$～$i]$具有长度为$i-next[?]$
        的循环元，即$s[1$～$i-next[?]]$。
        (用与结论一同样的证明方法可以推导出结论二)
        (由此处可知，$i-next[?]$想用作循环元要满足的
         条件是：$i-next[?]$可整除$i$)。

#### 结论三：

任意一个循环元的长度必定是最小循环元长度的倍数

#### 结论四：

如果$i-next[i]$不可整除$i$，$s[1$～$i-next[?]]$一定
        不能作为$s[1$～$i]$的循环元。
        
--------------


### 关于结论四的证明和扩展：


①.如果$s[1$～$i-next[i]]$不能作为$s[1$～$i]$循环元，那么
   $s[1$～$i-next[?]]$也都一定不能作为$s[1$～$i]$的循环元。
   (即结论四)  
   
②.如果$i-next[i]$不可整除$i$，$s[1$～$i]$一定不存在循环元。  

③.如果$i-next[i]$不可整除$i$，$i-next[?]$也都一定不可整除$i$。  

④.如果$s[1$～$m]$是$s[1$～$i]$的循环元，$next[i]$一定为$i-m$($i-m$一定为
   $next[i]$)。(在算法竞赛进阶指南上有这么一句话：如果$s[1$～$m]$为$s[1$～$i]$的循
   环元，$i-m$一定是$next[i]$的“候选项”，与此处意义略有不同)

⑤.若$m=i-next[i]$，$j=next[?]$，$next[j]=j-m$。(无论$m$可否整除$i$)
   (由④扩展而来)

------------


#### 一些题外话：


关于③的证明，有一个很有趣的想法。
     有两个数$a$,$c$和一个数的集合$b$，且$b$与$a$有一定的关系(限制)。
 已知$a$不可整除$c$，证明$x(x∈b$)不可整除$c$(~~目前尚未成功~~)。
     虽然表面上看起来并没有什么用，但这种思想把图形匹配转
 化为了代数证明。  
 如果有大佬感兴趣可以思考一下。。。

 
###### 附：来自某**李姓**Math大佬。


------------


#### ②③④比较好理解，这个⑤是个什么意思呢？



![](https://i.loli.net/2019/03/18/5c8efbd170406.png)

其实不难懂，通俗点说就是$i-next[?]$一定是在$m$的倍数处
  $(m,2m,3m...)$，如果有循环，也可以说是$i-next[?]$一定在循环
  节点上,或者说是一定在我们先前图片中框选的黑色块的边界相
  邻处，不可能在某个黑色块的中间（如图红色为不可能的情况）  
  
注意一下这个等式：$i-next[j]=i-j+m$  
可以化简为：$next[j]=j-m$

那么可以发现每个$next[?]$和$next[next[?]]$之间刚好相差m，
  只是要由⑤推导①的话，用化简前的样子似乎会更好懂一些。


------------


#### 假如④⑤得证，那么它们和①有什么关系呢？


如果$i-next[?]$一定是在$m$的倍数处$(m=i-next[i])$，
因为当$m$不可整除$i$时，$m$的倍数也不可整除$i$，
所以$i-next[?]$均不满足作为$s[1$～$i]$循环元的条件(前面已
提到过“条件”具体指什么)。

因此，⑤$→$①得证。


-----------


#### 如何证明④或者⑤？


-----------

![](https://i.loli.net/2019/03/18/5c8efe816a972.png)

如图，$j=next[i]$，$m=i-next[i]$  
先按照与之前相同的方法先将$s[1$～$i]$划分成$K$个黑色块

-----------

![](https://i.loli.net/2019/03/18/5c8efe85e6629.png)

$j0=next[j]$，$n=i-next[j]$，假设n不在m的倍数处，如图红色。

------------


![](https://i.loli.net/2019/03/18/5c8efe89b3425.png)

同样的，框选出红色块。


------------

![](https://i.loli.net/2019/03/18/5c8efe90a567b.png)

![](https://i.loli.net/2019/03/18/5c8efea742d14.png)

然后再作一些辅助线。接下来就开始推理。  

设$v=j-j0$。  

先看左边：$s[1$～$1+v]=s[m$～$m+v]$，$s[1+v$～$1+2v]=s[m+v$～$m+2v] $ 

再看右边：  $s[1$～$1+v]=s[m+v$～$m+2v]$  

综合可得：$s[1$～$1+v]=s[m$～$m+v]=s[m+v$～$m+2v]=s[1+v$～$1+2v]$
 
 
无限的推进，再推进，辅助线划分出的长度为v的区域全部相等，直至边界。而此时的边界出现了两种情况：  
 
    ⑴v可整除i。
此时刚好将$s[1$～$i]$分成了若干个完全相同的长度为$v$的小块，明显形成了循环元$s[1$～$v]$，那么$next[i]$至少应为$i-v$，这与之前的$next[i]=j$相矛盾。  
   
	⑵v不可整除i。
观察下列图片，你发现了什么？ 


![](https://i.loli.net/2019/03/18/5c8efeadd7577.png)

将蓝圈处放大，发现了一种交叉相等的情况(如图绿色处)。

![](https://i.loli.net/2019/03/18/5c8efeb075a81.png)

再把它压扁，并取几个新的名字$1',m',j',i'$。此时它变得和初始
  的情况一模一样，于是经过相同的操作后，再一次使出了无限
  推进，假如每次的$v'$都不可整除$m'$，那么就一路推了边界：$v'=1$。
  $1$可以整除任何数，于是$s[1$～$i]$形成了长度为$1$的循环元，矛盾。

![](https://i.loli.net/2019/03/18/5c8efeb9079ee.png)

当n不在m的倍数处时，一定会出现矛盾，所以假设不成立。

因此④得证。同理⑤也得证。

----------

# 完结附代码：

```cpp
#include<cstdio>
int t,i,j,n,nex[1000005];char a[1000005];
int main(){
    while(scanf("%d",&n),n){
        scanf("%s",a+1);
        printf("Test case #%d\n",++t);
        for(i=2,j=0;i<=n;i++){//最基本的 next[] 数组求法 
            while(j&&a[i]!=a[j+1])j=nex[j];
            if(a[i]==a[j+1])j++;nex[i]=j;
        }
        for(i=2;i<=n;i++)//由于1～1只有一个字母，只能是它本身构成长度为1的循环，所以从2开始枚举 
            if(i%(i-nex[i])==0&&nex[i])//判断时还要注意nex[i]是否为0 
                printf("%d %d\n",i,i/(i-nex[i]));
//如果i含有长度大于1的最小循环元，输出i的长度(即i)以及最大循环次数K(即i-nex[i]) 
        printf("\n");//记得输出一个空行 
    }
}

```

~~写了这么多证明，结果最后代码简单得不要不要的。。。。。~~

---

## 作者：shs_ryf (赞：11)

这道题是lrj讲kmp算法时候的例题, 所以用kmp是必须的了. 但是他在正确性这一块讲得很模糊, 好像才两三行就略过了(当然也可能是我太菜无法理解). 所以我想来尝试较为严谨地证明一下这个做法的正确性.



先做几个约定: 以下的大写英文字母均表示字符串, 本篇中字符串下标均从 0 开始.令 $i > 0$ . $S + i - 1$ 表示字符串S的前缀 $S_0$ 到 $S_{i - 1}$ , 容易看出这个前缀长度为 $i$ .若有一个长度不超过 $i$ 的字符串的集合, 使这个集合中的每一个元素既是 $S + i - 1$ 的前缀, 又是它的后缀, 记这个集合为 $Ω$ , 那么这个集合中长度最长的元素即为 $S + f_i - 1$ , 长度为 $f_i$ . 我们称 $f_i$ 为这个子串 $S + i - 1$ 的前缀数组(学过kmp算法的应该能理解这个定义). 显而易见 $f_i ≥ 0$ . 另设最大循环次数为 $k$ . 定义 $n * X$ 表示 $X$ 字符串重复了 $n$ 次, $X + Y$ 表示在串 $X$ 后接上串 $Y$ , $X.length()$ 表示 $X$ 的长度.



引理1: 对于一个前缀 $S + i - 1$ , 若 $f_i = 0$ , 则不存在 $k > 1$ 的循环元.

证明: 反证法. 若存在一个循环元 $A$ , 使得 $k >  1$ , 那么一定存在一个 $f'_i = A.length()$ , 使得 $S + f'_i - 1 \in Ω$ , 矛盾, 所以原命题成立.



引理2: 对于一个前缀 $S + i - 1$ , 若存在最短循环元 $A$ , 则 $A.length() ≥ i - f_i$ 

证明: 反证法. 若原命题不成立, 则 $A.length() < i - f_i$ , 即 $i - A.length() > f_i$ . 由于 $A$ 是循环元, 那么一定存在一个 $f'_i = i - A.length()$ , 使得 $S + f'_i - 1 \in Ω$ . 又 $f'_i > f_i$ , 矛盾, 所以原命题成立.



根据引理1, $f_i = 0$ 时无解, 所以接下来我们讨论 $f_i ≠ 0$ 的两种情况.



我们首先证明: 对于一个前缀 $S + i - 1$ , 若有 $i \ \text{mod}\ (i - f_i) = 0$ , 那么存在一个最小的长度为 $i - f_i$ 的最小循环元 $S + i - f_i - 1$ , 我们把它记作 $A$ .

证明分两部分, 先证明在上述条件下 $A$ 是一个循环元.

我们令 $j = \frac{i}{i - f_i}$ , 那么可以将 $S$ 划分成 $j$ 个部分, 记这 $j$ 个部分依次为 $D_0, D_1, D_2, ..., D_{j - 1}$ , 其中 $D_0 = A$ . 由于 $S + f_i - 1 \in Ω$ , 那么 $D_0 = D_1 = D_2 = ... = D_{j - 1} = A$ , 所以 $A$ 是一个循环元.

再证明 $A$ 为长度最短的循环元. 由引理2, 因为 $A.length() = i - f_i$ , 所以 $A$ 为长度最短的循环元.



接着我们看到第二种情况, 对于一个前缀 $S + i - 1$ , 若 $i \ \text{mod}\ (i - f_i) ≠ 0$ , 可以证明不存在 $k > 1$ 的循环元.

若这样的最短循环元 $A$ 存在, 由引理2可得 $A.length() >= i - f_i$ . 再由于 $i \ \text{mod}\ (i - f_i) ≠ 0$ , 因此 $A.length() ≠ i - f_i$ . 所以 $A.length() > i - f_i$ .

令串 $S + i  - f_i- 1 = B$ , 并令 $A = B + C$ , 由上述证明可得 $C$ 必存在且非空. 那么由于 $S = k * A$ , 则 $S = k * (B + C) = B + (k - 1) * (C + B) + C$ . 又由于 $S + i  - f_i- 1 = B$ , 取该表达式的后缀, 可得 $S = (k - 1) * (C + B) + C + X$ , 其中 $X.length() = B.length()$ . 因为 $(B + C).length() = (C + B).length()$ , 所以 $B + C = C + B$ 且 $B + C = C + X$ , 于是可得 $C + B = C + X$ , 因此 $B = X$ . 即 $S = k * (B + C) = k * (C + B)$ . 取前一表达式的后缀与后一表达式的前缀, 由于 $S + f_i - 1 \in Ω$ , 可得 $S + f_i - 1 = (k - 1) * (C + B) + C = (k - 1) * (B + C) + B$ , 又因为 $C +  B = B + C$ , 可以得出 $B = C$ .

因此一定可以找到比 $A$ 更短的循环元 $B$ , 与假设 $A$ 最短矛盾, 所以不存在最短循环元, 即不存在循环元.



综上所述, 当且仅当 $ f_i > 0 \ \&\&\  i \ \text{mod}\ (i - f_i) = 0$ 时存在循环元, 且最短循环元长度为 $i - f_i$ , 循环次数 $k = \frac{i}{i - f_i}$ .



在这个证明中我大量使用了反证法, 并且定义了一些符号, 可能需要仔细看. 中间有一些推导过程需要对kmp性质较为熟悉, 然后就会发现还是比较明显的. 第一次写这样的证明过程, 好激动啊! 当然我没经过什么专业训练, 要是有啥问题就请指出哈.

以下是代码, 其实就是结论 + kmp前缀数组的模板.

```cpp
#include<iostream>
using namespace std;

int f[1000007];
int main(){
    ios::sync_with_stdio(false);
    int t, n;
    string s;
    cin >> t;
    for(int h = 1; h <= t; ++h){
        cout << "Test case #" << h << "\n";
        cin >> n >> s;
        f[0] = f[1] = 0;
        for(register int i = 1; i < n; ++i){
            int j = f[i];
            while(j && s[j] != s[i])
                j = f[j];
            f[i + 1] = s[i] == s[j] ? j + 1 : 0;
        }
        for(int i = 2; i <= n; ++i){
            if(f[i] && i % (i - f[i]) == 0){
                cout << i << " " << i / (i - f[i]) << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}
```



---

## 作者：Strelitzia (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/SP263)

---

前置知识：$\texttt{KMP}$

做这道题前可以先做一下[Power Strings](https://www.luogu.com.cn/problem/UVA10298)，其实这道题就是 $\text{Power Strings}$ 多了一点判读。

我们要深刻理解这个 $\text {pre}$ 这个数组的含义，它也是 $\texttt{KMP}$ 的精髓。

这里要引入一个~~结论~~?

就是长度为 $\operatorname n$ 的字符串，如果 $n \equiv 0 \mod (n -nxt_n)$，那循环节出现的次数就为 $n / (n - nxt_n)$。

具体证明就可以看这篇[博客](https://www.luogu.com.cn/blog/hzz/solution-uva10298)。

代码还有一点小细节，要注意。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 1000005;

char a[maxn],b[maxn],c[maxn];
int lena,lenb,f[maxn];

int pre[maxn],cnt;

void make_pre(char b[],int lenb) {
	pre[1] = 0;
	int j = 0;
	for (int i = 2 ; i <= lenb ; ++ i) {
		while (j && b[i] != b[j + 1]) j = pre[j];
		if (b[i] == b[j + 1]) j ++;
		pre[i] = j;
	}
}

int main () {
	int times;
	read(times);
	int www = 0;
	while (times --) {
		read(lena);
		scanf("%s",a + 1);
		make_pre(a,lena);
		printf("Test case #%d\n",++ www);
		for (int i = 2 ; i <= lena ; ++ i) {
			if (i % (i - pre[i]) == 0 && i / (i - pre[i]) > 1) {
				printf("%d %d\n",i,i / (i - pre[i]));
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Mikran (赞：1)

# PERIOD - Period 题解

题解全是 KMP 啊……

但是为什么不用 Hash 呢？

转换一下题意就是求对于每一个 $S[1,i]$，求一个最小的 $j(j<i)$ 满足 $S[1,i]$ 由若干个 $S[1,j]$ 拼起来，设 $ans_i=i/j$。

我们可以枚举每一个 $S[1,j]$，然后暴力地往后匹配 $S[cnt\times j+1,(cnt+1)\times j](cnt > 1)$，如果匹配上了，那么 $ans_{(cnt+1)\times j}=\max(ans_{(cnt+1)\times j},cnt)$，如果匹配失败，立刻退出，枚举到下一个 $j$。

匹配两个串用 Hash 做到 $O(1)$。

然后这个看似很暴力的枚举实际上是 $O(n\log n)$ 的（参考埃式筛的复杂度证明）。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define ull unsigned long long
#define __int32 int
#define __int64 long long
#define db long double
#define eps 1e-12
void Freopen() { freopen(".in", "r", stdin), freopen(".out", "w", stdout); }
const int N = 1e6 + 10, M = 2e5 + 10, inf = 1e9, mod = 998244353;
const ull base = 137;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ! isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x *= f;
}
void write( int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
using namespace std;
int n, tot;
char s[N];
ull hsh[N], pw[N];
ull query( int l, int r) { return hsh[r] - hsh[l - 1] * pw[r - l + 1]; }
int ans[N];
void solve( int n) {
	scanf("%s", s + 1);
	for ( int i = 1; i <= n; i ++) hsh[i] = hsh[i - 1] * base + s[i], ans[i] = 0;
	for ( int i = 1; i <= n; i ++) {
		int res = 0;
		for ( int l = 1; l + i - 1 <= n; l += i) {
			int r = l + i - 1;
			if (query(l, r) != hsh[i]) break ;
			res ++;
			if (r != i) ans[r] = max(ans[r], res);
		}
	}
	printf("Test case #%d\n", ++ tot);
	for ( int i = 2; i <= n; i ++) if (ans[i]) printf("%d %d\n", i, ans[i]);
	puts("");
}
signed main() { 
	pw[0] = 1;
	for ( int i = 1; i < N; i ++) pw[i] = pw[i - 1] * base;
	for ( int t = read(); t; t --) n = read(), solve(n);
}

```

---

## 作者：l_x_z2020 (赞：1)

（第一次发题解，如有小错请见谅）

本题KMP裸题，适合KMP新手练手。~~读者：又是废话~~

------------
直接上结论：主串A，模式串B。
        **当A[i]和B[j]不匹配时，可以固定i不变，而只改变j的值，使得其重新匹配。**~~（本人过蒟，证明什么的看看楼下几位大佬的吧）~~

所以新增一个根据模式串建立的数组next[i],表示**以i结尾的非前缀子串**与**B串的前缀**能够匹配的最长长度!!

看着有些麻烦，举个栗子好好想想就明白了！

------------
假设B={a,b,a,b,a,b,c,a}

当i=2时，j=1，不匹配，所以next[2]=0。

当i=3时，j=1，匹配的子串为a，所以next[3]=1。

当i=4时，j=2，匹配的子串为ab，所以next[4]=2。

当i=7时，j=1，不匹配，所以next[7]=0。

记住初始化——当i=1时，next[1]=0（看定义不解释）。

~~（还不会插入图片，再次表达歉意）~~

最后直接上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ne[1000005],n,T;
char a[1000005];
int main()
{
    int i,j,k,tot=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(ne,0,sizeof(ne));//代码千万条，初始化第一条
        scanf("%s",a+1);//从1开始读入
        ne[1]=0;//初始化
        for(i=2,j=0;i<=n;i++)
        {
            while(j>0&&a[i]!=a[j+1])j=ne[j];
            if(a[i]==a[j+1])j++;
            ne[i]=j;
        }//根据定义预处理next数组
        printf("Test case #%d\n",++tot);
        for(i=2;i<=n;i++)
            if(i%(i-ne[i])==0&&i/(i-ne[i])!=1)
            	printf("%d %d\n",i,i/(i-ne[i]));
        printf("\n");//代码不换行，毒瘤两行泪
    }
}
```
（如有错误，欢迎批评指导）

---

## 作者：Skies (赞：0)

# 前言
看到别的9篇题解都是$kmp$，~~蒟蒻不会~~

SP的公用账户又炸了，我的代码没有评测过，但应该没有问题 （update:2021/2/26  已经A掉了）
# solution
这里提供一个**Z函数**的思路

 $Z$ 函数，又称扩展 $KMP$ , 是求后缀与原串的 $LCP$ （最长公共前缀）

这里就不多讲了，   [不会戳这里](https://oi-wiki.org/string/z-func/)

先上个模板

```cpp
void Z()
{
	int l=0,r=0;
	for(int i=1;i<n;i++)
	{
		if(i<r&&z[i-l]<r-i+1)z[i]=z[i-l];
		else{
			z[i]=max(0,r-i+1);
			while(s[z[i]]==s[i+z[i]])z[i]++;
			if(i+z[i]-1>r)r=i+z[i]-1,l=i;
		}
	}
}
```


求出来后，我们看看要满足什么样的性质才能算是循环节。

对于每个 $z[i]$ ,我们可以把 $ s[0....i-1]$ 当做循环节（前 $i$ 位），然后逐个遍历可能的末端点即可


画一个图方便李姐

![](https://cdn.luogu.com.cn/upload/image_hosting/r2yexz3s.png)

根据 $Z$ 函数定义，上下的红色相同，但红色与粉色相同，同理可以得出绿色与蓝色也相同，所以整个串都是由长度为i的循环节构成的。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n;
char s[N];
int z[N];
void Z()
{
	int l=0,r=0;
	for(int i=1;i<n;i++)
	{
		if(i<r&&z[i-l]<r-i+1)z[i]=z[i-l];
		else{
			z[i]=max(0,r-i+1);
			while(s[z[i]]==s[i+z[i]])z[i]++;
			if(i+z[i]-1>r)r=i+z[i]-1,l=i;
		}
	}
}
int ans[N];
int main() 
{
	cin>>T;
	for(int ca=1;ca<=T;ca++)
	{
		scanf("%d%s",&n,&s);
		printf("Test case #");cout<<ca<<endl;
		
		Z();z[0]=n;
		
		for(int i=1;i<n;i++)
		{
			int len=i;
			for(int j=i+i-1;j<i+z[i];j+=len)
			{
				
				ans[j]=max(ans[j],(j+1)/len);
			}
		}
		for(int i=0;i<n;i++)
		{
			if(ans[i])
			{
				printf("%d %d\n",i+1,ans[i]);
				ans[i]=0;
			}
		}
		memset(z,0,sizeof z);
		puts("");
	}
	return 0;
}
```



---

## 作者：yf最qhhh (赞：0)

kmp算法的简单题。

这道题没有什么难点，唯一需要注意的是输出的格式问题（上午在学校做的时候错了好久qwq）

如果不知道什么是KMP算法，大概总结一下就是：用来查找一个主串 $A$ 里模式串 $B$ 出现了几次。虽说它也是从左往右遍历，但 $i$ 的值不用回退，只需改变 $j$ 的值就好了。

~~还是听不懂咋办~~

说简单点，查找永远只会向前查找，不会后退。

再来看这道题。

~~原谅蒟蒻不会证明~~，对于第 $i$ 次循环，首先需要满足条件 $i\mod i-next_{i}$，如果满足，循环节长度为 $i-next_{i}$，循环次数即为 $\frac{i}{t-next_{i}}$。

注意：循环节的循环次数必须大于2。

所以这道题只需要在kmp算法的模板上稍加修改。

核心代码如下：
```cpp
    scanf("%lld",&n);
    scanf("%s",s+1);
    printf("Test case #%lld\n",++tot);
    next[1]=0;//初始化
    for(i=2;i<=n;i++){
        while(s[i]!=s[j+1]&&j) j=next[j];
        if(s[i]==s[j+1]) j++;
        next[i]=j;//模板
        if(next[i]&&i%(i-next[i])==0) 
            printf("%lld %lld\n",i,i/(i-next[i]));//刚刚所说的结论
    }
    printf("\n");
```


---

## 作者：ZRHan (赞：0)

利用KMP的nxt数组，首先如果一个子串是循环节，那么他第一次出现循环的时候一定在偶数的位置。比如说：
```latex
  abcabcabcabc
       ^  ^  ^
i      6  9  12
k      2  3  4
```
在i=6的位置可以是一个可行的前缀。而且当且仅当它的nxt是$\frac{i}{2}$，它才是k=2的循环节。在例子中nxt[6]显然等于3。它的周期$t$会等于$\frac{i}{2}$也就是3。


然后可以按照类似线性筛的方法枚举它的每个周期，即k=3，k=4，k=5......
如果某个$k$能成为循环，那么此时的nxt应该是$(k-1)*t$。比如i=9的显然是一个可行的循环，此时t=3，k=3，而nxt[i]=6。


期间用vis记录，访问过的就跳过，就可以$O(n)$解决。

```cpp
#include<cstdio> 
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 1e6+5;
int nxt[maxn], n;
char s[maxn];
bool vis[maxn];

void getnxt()
{
    for(int i=2, j=0; i<=n; ++i)
    {
        while(j>0 && s[i]!=s[j+1]) j = nxt[j];
        if(s[i]==s[j+1]) ++j;
        nxt[i] = j;
    }
}

int main()
{
    int qwq=0;
    scanf("%d", &qwq);
    for(int qqq=1; qqq<=qwq; ++qqq)
    {

        scanf("%d", &n);
        if(n==0) return 0;
        scanf("%s", s+1);

        printf("Test case #%d\n", qqq);
        getnxt();

        for(int i=2; i<=n; i+=2)
        {
            if(vis[i]) continue;
            if(nxt[i] == i>>1)  //当且仅当它的nxt是i/2，它才是k=2的循环节
            {
                int t = i>>1;
                vis[i] = 1;
                printf("%d %d\n", i, 2);
                for(int j=i+t, cnt=1; j<=n; j+=t, ++cnt)  //枚举k=3，k=4，k=5... 
                {
                    if(vis[j]) continue;
                    if(nxt[j] == (cnt+1)*t) 
                    {
                        printf("%d %d\n", j, cnt+2);
                        vis[j] = 1;
                    }
                    else break;  
                    //如果已经不满足循环了，k就不能再加了，因为即使后面的满足也被这个不满足的部分中断 
                }
            }
        }

        puts("");
        
        //初始化 
        for(int i=0; i<=n; ++i)
        {
            vis[i] = nxt[i] = s[i] = 0;
        }
    }
    return 0;
}
```


---

## 作者：傅思维666 (赞：0)

一道KMP算法的练手好题。

大体的题目大意是这样的：

## 题目大意：

如果一个字符串S是由一个字符串T重复K次形成的，则称T是S的循环元。使K最大的字符串T称为S的最小循环元，此时的K称为最大循环次数。

现给一个给定长度为N的字符串S，对S的每一个前缀S[1~i]，如果它的最大循环次数大于1，则输出该前缀的最小循环元长度和最大循环次数。

## 题解：

一道KMP算法的题目，如果对KMP算法还是没有什么深刻的理解或者还没学KMP算法的，请移步我的这篇博客，讲解还算详细：

[KMP算法详解]( https://www.cnblogs.com/fusiwei/p/11945030.html )

一开始拿到题没什么思路（我还是太菜了）

后来发现，对给出的串$S$自匹配求出$nxt$数组之后，对于每一个$i$，一定会有这么一个结论：
$$
S[1\,\,to\,\,nxt[i]]=S[i-nxt[i]+1\,\,to\,\,i]
$$
这是通过KMP算法对$nxt$数组的定义得来的。

那么，既然这两个东西是相等的，那么在对这个子串进行匹配的时候，这个循环节长度就应该是$i-nxt[i]$，然后循环次数当然就是$i/(i-nxt[i])$，当然，前提需要是$i\%(i-nxt[i])==0$。

代码如下：

```cpp
#include<cstdio>
using namespace std;
const int maxl=1e6+10;
int n,tot;
char s[maxl];
int nxt[maxl];
int main()
{
    while(~scanf("%d",&n) && n)
    {
        scanf("%s",s+1); 
        tot++;
        printf("Test case #%d\n",tot);
        nxt[1]=0;
        for(int i=2,j=0;i<=n;++i)
        {
            while(s[i]!=s[j+1] && j) 
                j=nxt[j];
            if(s[i]==s[j+1]) 
                j++;
            nxt[i]=j;
            if(nxt[i]!=0 && i%(i-nxt[i])==0) 
                printf("%d %d\n",i,i/(i-nxt[i]));
        }
        printf("\n");
    }
    return 0;
}
```


---

## 作者：陷语 (赞：0)

### Period

**题目意思：**

给你一个字符串，要你求这个字符串各个前缀的最小循环元，和最大循环次数K

**思路：**

对于每一个字符串， 我们都可以先让它进行自我匹配，求出每一个next[i]，通过题目意思与样例观察，我们可以发现一个前缀要符合题目条件有循环元，那这个前缀的长度一定是大于1的，并且最大循环次数一定也是大于1的，所以我们可以得到以下性质：

**1.当前循环元的长度一定可以整除当前前缀的长度；**

**2.当前循环元的长度整除当前前缀的长度得到的最大循环次数一定是 >= 2的；**

**附上代码：**
```cpp
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 1000100;

int n, cnt, t;
char c[N];
int nex[N];

int main() {
//	freopen("in.txt", "r", stdin);
	scanf("%d", &t);
	while(t--) {
		
		scanf("%d", &n);
		scanf("%s", c + 1);
		nex[1] = 0;
		//进行自我匹配 
		 for(int i = 2, j = 0; i <= n; ++i) {
		 	while(j > 0 && c[i] != c[j + 1]) j = nex[j];
		 	if(c[i] == c[j + 1]) ++j;
		 	nex[i] = j;
		 }
		 
		 printf("Test case #%d\n", ++cnt);
		 for(int i = 2; i <= n; ++i) {
		 	if(!(i % (i - nex[i])) && (i / (i - nex[i])) >= 2)
		 		printf("%d %d\n", i, i / (i - nex[i]));
		 }
		 puts("");
	}
	return 0;
}
```


---

## 作者：让风忽悠你 (赞：0)

[原题](https://www.luogu.com.cn/problem/SP263)

## 题意

如果一个字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，则称 $T$ 是 $S$ 的循环节。使 $K$ 最大的字符串 $T$ 称为 $S$ 的最小循环节，此时的 $K$ 称为最大循环次数。

现给定一个字符串 $S$，如果它的任意一个**前缀的最大循环次数**大于 1，就输出前缀的长度和最大循环次数。

## 做法

提到字符串的最小循环节，考虑使用 KMP。这里引入一个结论：在 KMP 中，对于任意一个长度为 $n$ 的字符串，其最小循环节长度为 $n-next_n$。解释一下,$next$ 数组记录的是上一个与当前字符串相同的字符串的位置，所以如果字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，当前字符串和上一个与其相同的字符串的位置差即为最小循环节的长度。所以，最大循环次数即为 $\text{字符串长度} \div \text{最短循环节长度}$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define N 1000005

using namespace std;

int n,j,T,cnt;
int nxt[N];
char s[N];

inline void clear(){
	nxt[1]=nxt[0]=0;
	j=0;
} // 清空，避免影响下一组数据操作 

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf(" %s",s+1);
		clear();
		printf("Test case #%d\n",++cnt);
		for(int i=2;i<=n;++i){
			while(j && s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) ++j;
			nxt[i]=j;
		} // KMP 基本操作，没啥好说的
		for(int i=2;i<=n;i++)
			if(nxt[i] && i%(i-nxt[i])==0) // 判断当前前缀是否符合要求 
				printf("%d %d\n",i,i/(i-nxt[i]));
		printf("\n"); // 记得过行 
	}
	return 0;
}
```


---

## 作者：ZJsheep (赞：0)

# Explanation

一道KMP模板应用题。

PS：这个算法的名字比较诡异是因为它由三位伟大的科学家共同设计：*D.E.Knuth*，*J.H.Morris*和*V.R.Pratt*。

KMP模板长这样（详见《算法竞赛进阶指南》p.66 或 [洛谷题解](https://www.luogu.org/problemnew/solution/P3375))：

```cpp
void KMP() {
    Next[1] = 0;
    for (int i = 2, j = 0; i <= lb; i++) {
        while (j > 0 && b[i] != b[j + 1]) j = Next[j];
        if (b[i] == b[j + 1]) j++;
        Next[i] = j;
    }
    for (int i = 1, j = 0; i <= la; i++) {
        while (j > 0 && (j == lb || a[i] != b[j + 1])) j = Next[j];
        if (a[i] == b[j + 1]) j++;
        F[i] = j;
        if (j == lb) cout << i - lb + 1 << endl;
    }
}
```

其中，如果j是Next[i]的“候选项”，那么Next[i]下一个“候选项”一定是Next[j]。这是因为下一个“候选项”首先要与j匹配，才有可能与i匹配。而满足这一性质的最大值为Next[j]。

再来看这道题。首先，如果i-len就是Next[i]的候选项，那么显然len有可能是循环节。说明充分性：i-len就是Next[i]的候选项，即str[i…len-1]=str[len+1…i]。取两个子串前len个字符，显然也相等。

还有一点，一个子串一定要出现两次以上才能被称作“循环节”，因此在满足整除的条件下，还要保证当前串长度除以要检查的子串长度大于1。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000000 + 10;
int Next[MAX_N], n, t;
char str[MAX_N];

int main() {
    scanf("%d", &t);
    for (int k = 1; k <= t; k++) {
        scanf("%d%s", &n, str + 1);
        printf("Test case #%d\n", k);
        Next[1] = 0;
        for (int i = 2, j = 0; i <= n; i++) {
            while (j > 0 && str[i] != str[j + 1]) j = Next[j];
            if (str[i] == str[j + 1]) j++;
            Next[i] = j;
        }
        for (int i = 1; i <= n; i++) {
            if (i % (i - Next[i]) == 0 && i / (i - Next[i]) > 1)
            // 子串一定要出现两次以上才能被称作“循环节”
                printf("%d %d\n", i, i / (i - Next[i]));
        }
    }
    return 0;
}
```

# Reference

《算法竞赛进阶指南》p.69

---

