# 题目信息

# Repetitions Decoding

## 题目描述

Olya has an array of integers $ a_1, a_2, \ldots, a_n $ . She wants to split it into tandem repeats. Since it's rarely possible, before that she wants to perform the following operation several (possibly, zero) number of times: insert a pair of equal numbers into an arbitrary position. Help her!

More formally:

- A tandem repeat is a sequence $ x $ of even length $ 2k $ such that for each $ 1 \le i \le k $ the condition $ x_i = x_{i + k} $ is satisfied.
- An array $ a $ could be split into tandem repeats if you can split it into several parts, each being a subsegment of the array, such that each part is a tandem repeat.
- In one operation you can choose an arbitrary letter $ c $ and insert $ [c, c] $ to any position in the array (at the beginning, between any two integers, or at the end).
- You are to perform several operations and split the array into tandem repeats or determine that it is impossible. Please note that you do not have to minimize the number of operations.

## 说明/提示

In the first test case, you cannot apply operations to the array to make it possible to split it into tandem repeats.

In the second test case the array is already a tandem repeat $ [5, 5] = \underbrace{([5] + [5])}_{t_1 = 2} $ , thus we can do no operations at all.

In the third test case, initially, we have the following array: $ $$$[1, 3, 1, 2, 2, 3]. $ $  After the first insertion with  $ p = 1, c = 3 $ :  $ $ [1, \textbf{3, 3}, 3, 1, 2, 2, 3]. $ $  After the second insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 2, 2, 3]. $ $  After the third insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 3, 3, 2, 2, 3]. $ $  After the fourth insertion with  $ p = 10, c = 3 $ :  $ $ [1, 3, 3, 3, 1, 3, 3, 3, 3, 2, \textbf{3, 3}, 2, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([1, 3, 3, 3] + [1, 3, 3, 3])}_{t_1 = 8} + \underbrace{([3, 2, 3] + [3, 2, 3])}_{t_2 = 6}. $ $ </p><p>In the fourth test case, initially, we have the following array:  $ $ [3, 2, 1, 1, 2, 3]. $ $  After the first insertion with  $ p = 0, c = 3 $ :  $ $ [\textbf{3, 3}, 3, 2, 1, 1, 2, 3]. $ $  After the second insertion with  $ p = 8, c = 3 $ :  $ $ [3, 3, 3, 2, 1, 1, 2, 3, \textbf{3, 3}]. $ $  After the third insertion with  $ p = 5, c = 3 $   $ $ [3, 3, 3, 2, 1, \textbf{3, 3}, 1, 2, 3, 3, 3]. $ $  After the fourth insertion with  $ p = 6, c = 2 $ :  $ $ [3, 3, 3, 2, 1, 3, \textbf{2, 2}, 3, 1, 2, 3, 3, 3]. $ $  After the fifth insertion with  $ p = 7, c = 1 $ :  $ $ [3, 3, 3, 2, 1, 3, 2, \textbf{1, 1}, 2, 3, 1, 2, 3, 3, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([3] + [3])}_{t_1 = 2} + \underbrace{([3, 2, 1] + [3, 2, 1])}_{t_2 = 6} + \underbrace{([1, 2, 3] + [1, 2, 3])}_{t_3 = 6} + \underbrace{([3] + [3])}_{t_4 = 2}. $ $$$

## 样例 #1

### 输入

```
4
2
5 7
2
5 5
6
1 3 1 2 2 3
6
3 2 1 1 2 3```

### 输出

```
-1
0
1
2
4
1 3
5 3
5 3
10 3
2
8 6 
5
0 3
8 3
5 3 
6 2 
7 1
4
2 6 6 2```

# AI分析结果

### 题目内容中文重写
### 重复解码

#### 题目描述
奥莉娅有一个整数数组 $ a_1, a_2, \ldots, a_n $。她想把它拆分成串联重复。由于这很少能实现，在此之前，她想进行若干次（可能为零次）以下操作：在任意位置插入一对相等的数字。请帮助她！

更正式地说：
- 串联重复是一个长度为 $ 2k $ 的偶数序列 $ x $，使得对于每个 $ 1 \le i \le k $，都满足条件 $ x_i = x_{i + k} $。
- 如果可以将数组 $ a $ 拆分成若干部分，每个部分都是数组的子段，并且每个部分都是串联重复，那么数组 $ a $ 可以拆分成串联重复。
- 在一次操作中，你可以选择任意一个数字 $ c $，并将 $ [c, c] $ 插入到数组的任意位置（开头、任意两个整数之间或结尾）。
- 你需要执行若干次操作，将数组拆分成串联重复，或者确定这是不可能的。请注意，你不必最小化操作次数。

#### 说明/提示
在第一个测试用例中，你无法对数组进行操作，使其能够拆分成串联重复。

在第二个测试用例中，数组已经是一个串联重复 $ [5, 5] = \underbrace{([5] + [5])}_{t_1 = 2} $，因此我们根本不需要进行任何操作。

在第三个测试用例中，最初，我们有以下数组：
$$[1, 3, 1, 2, 2, 3].$$
在第一次插入，$ p = 1, c = 3 $ 之后：
$$ [1, \textbf{3, 3}, 3, 1, 2, 2, 3].$$
在第二次插入，$ p = 5, c = 3 $ 之后：
$$ [1, 3, 3, 3, 1, \textbf{3, 3}, 2, 2, 3].$$
在第三次插入，$ p = 5, c = 3 $ 之后：
$$ [1, 3, 3, 3, 1, \textbf{3, 3}, 3, 3, 2, 2, 3].$$
在第四次插入，$ p = 10, c = 3 $ 之后：
$$ [1, 3, 3, 3, 1, 3, 3, 3, 3, 2, \textbf{3, 3}, 2, 3].$$
得到的数组可以表示为串联重复的连接：
$$ \underbrace{([1, 3, 3, 3] + [1, 3, 3, 3])}_{t_1 = 8} + \underbrace{([3, 2, 3] + [3, 2, 3])}_{t_2 = 6}.$$

在第四个测试用例中，最初，我们有以下数组：
$$ [3, 2, 1, 1, 2, 3].$$
在第一次插入，$ p = 0, c = 3 $ 之后：
$$ [\textbf{3, 3}, 3, 2, 1, 1, 2, 3].$$
在第二次插入，$ p = 8, c = 3 $ 之后：
$$ [3, 3, 3, 2, 1, 1, 2, 3, \textbf{3, 3}].$$
在第三次插入，$ p = 5, c = 3 $ 之后：
$$ [3, 3, 3, 2, 1, \textbf{3, 3}, 1, 2, 3, 3, 3].$$
在第四次插入，$ p = 6, c = 2 $ 之后：
$$ [3, 3, 3, 2, 1, 3, \textbf{2, 2}, 3, 1, 2, 3, 3, 3].$$
在第五次插入，$ p = 7, c = 1 $ 之后：
$$ [3, 3, 3, 2, 1, 3, 2, \textbf{1, 1}, 2, 3, 1, 2, 3, 3, 3].$$
得到的数组可以表示为串联重复的连接：
$$ \underbrace{([3] + [3])}_{t_1 = 2} + \underbrace{([3, 2, 1] + [3, 2, 1])}_{t_2 = 6} + \underbrace{([1, 2, 3] + [1, 2, 3])}_{t_3 = 6} + \underbrace{([3] + [3])}_{t_4 = 2}.$$

#### 样例 #1
##### 输入
```
4
2
5 7
2
5 5
6
1 3 1 2 2 3
6
3 2 1 1 2 3
```
##### 输出
```
-1
0
1
2
4
1 3
5 3
5 3
10 3
2
8 6 
5
0 3
8 3
5 3 
6 2 
7 1
4
2 6 6 2
```

### 综合分析与结论
这些题解的核心思路都是先判断数组中是否有数字出现奇数次，若有则无解。若没有，则通过构造的方式将数组拆分成串联重复。不同题解的构造方法有所不同，但大多是通过插入操作让相同的数字匹配，形成串联重复。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|DarkBird|找到第一个失配的数，往后找到与之相同的数，将中间的数全部插入一次，然后删除已匹配的部分，重复操作|用 `map` 统计数字出现次数，用 `vector` 存储数组和操作结果|如何通过插入操作使数组满足条件|4星|
|yzy1|用插入操作实现反转操作，从前往后遍历数组，若相邻元素不同则反转区间使相同元素相邻|用 `map` 统计数字出现次数，用 `vector` 存储数组和操作结果|如何实现反转操作|4星|
|KiloP|用至多 $n$ 次插入使不满足条件的数的个数减2，不断重复操作直到数组满足条件|用数组存储数组元素，用 `vector` 存储操作结果|如何通过插入操作减少不满足条件的数的个数|3星|
|Presentation_Emitter|将操作转换为添加回文串，将数组重组为目标串联重复，通过类似排序的过程使数组满足条件|用数组存储数组元素，用 `vector` 存储操作结果|如何将操作转换为添加回文串|3星|
|_Tooler_Fu_|找到第一个与 $a_1$ 相同的数，在其后插入中间的数，消除串联重复后继续操作|用 `map` 统计数字出现次数，用数组存储数组元素和操作结果|如何消除串联重复|3星|
|DaiRuiChen007|找到第一个与 $a_1$ 相同的数，在其后复制中间的数，消掉已匹配部分，重复操作|用 `map` 统计数字出现次数，用 `vector` 存储数组和操作结果|如何复制中间的数|3星|
|I_am_Accepted|找到 $a_1$ 之后第一个相同的数，在其后操作使两段相同，从新位置继续操作|用链表存储数组元素|如何用链表实现操作|3星|
|清烛|对前缀做翻转操作，将相同元素放在一起消掉，重复操作|用数组存储数组元素，用 `vector` 存储操作结果|如何实现前缀翻转操作|3星|
|Suzt_ilymtics|找到第一个数第二次出现的位置，通过插入操作使两段匹配，划分出一段，重复操作|用数组存储数组元素，用 `deque` 存储数组，用 `vector` 存储操作结果|如何通过插入操作使两段匹配|3星|

### 所选题解
- **DarkBird（4星）**
    - 关键亮点：思路清晰，代码简洁，通过简单的插入和删除操作实现数组的转换。
    - 核心代码：
```cpp
int n;
vector<int>v;
inline void solve(){
    cin>>n;
    map<int,int>cnt;
    v.clear();cnt.clear();
    for(int i=0,x;i<n;++i)cin>>x,v.push_back(x),++cnt[x];
    for(auto it:cnt)if(it.second%2==1){
        cout<<-1<<'\n';
        return;
    }
    vector<int>ans;
    vector<pair<int,int> >opr;
    int fnt=0;
    for(;v.size();){
        int i=0;
        for(int j=i+1;j<v.size();++j){
            if(v[i]==v[j]){
                ans.push_back(2*(j-i));
                int len=j-i-1;
                for(int t=0;t<len;++t)opr.push_back(mp(fnt+1+t+j,v[t+1]));
                fnt+=2*len+2;
                reverse(v.begin()+1,v.begin()+j);
                v.erase(v.begin()+j);
                v.erase(v.begin());
                break;
            }
        }
    }
    cout<<opr.size()<<'\n';
    for(auto p:opr)cout<<p.first<<' '<<p.second<<'\n';
    cout<<ans.size()<<'\n';
    for(auto i:ans)cout<<i<<' ';cout<<'\n';
}
```
- **yzy1（4星）**
    - 关键亮点：将插入操作转换为反转操作，思路新颖，代码实现较为清晰。
    - 核心代码：
```cpp
void Work(){
    map<int,int> mp1;
    vector<int>ans;
    vector<pair<int,int>>op;
    cin>>n;re(i,n)cin>>a[i],++mp1[a[i]];
    each(x,mp1)if(x.second%2==1)return cout<<"-1\n",void();
    int dlt=0;
    re(i,n-1){
        while(a[i]!=a[i+1]){
            int pos=-1;
            rep(j,i+1,n)if(a[j]==a[i]){pos=j;break;}
            int len=pos-i;
            rep(j,i,i+len-1)op.push_back({j+len+dlt-1,a[j]});
            reverse(a+i,a+i+len);
            ans.push_back(len*2);
            dlt+=len*2;
        }
        ans.push_back(2),++i;continue;
    }
    cout<<op.size()<<'\n';
    each(x,op)cout<<x.first<<' '<<x.second<<'\n';
    cout<<ans.size()<<'\n';
    each(x,ans)cout<<x<<' ';
    cout<<'\n';
}
```

### 最优关键思路或技巧
- **操作转换**：将题目给定的插入操作转换为反转操作或添加回文串操作，简化问题的处理。
- **贪心匹配**：每次找到第一个数和与之相同的数，通过插入操作使它们匹配，逐步减少不满足条件的数的个数。

### 可拓展之处
同类型题可能会改变操作规则或数组的限制条件，类似算法套路可以应用于字符串处理、序列构造等问题，关键在于如何通过给定的操作将序列转换为满足条件的形式。

### 推荐洛谷题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：考察栈的应用和序列构造。
- [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：考察动态规划和序列处理。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：考察动态规划和组合问题。

### 个人心得摘录与总结
- **I_am_Accepted**：骄傲地使用多年没写的链表过了此题。总结：可以尝试使用不同的数据结构解决问题，可能会有意外收获。
- **_Tooler_Fu_**：其实赛时只过了 A B ，C 都 FST 了 /kk。总结：比赛中可能会出现失误，需要不断练习提高自己的解题能力和稳定性。

---
处理用时：61.48秒