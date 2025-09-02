# 题目信息

# Carousel

## 题目描述

The round carousel consists of $ n $ figures of animals. Figures are numbered from $ 1 $ to $ n $ in order of the carousel moving. Thus, after the $ n $ -th figure the figure with the number $ 1 $ follows. Each figure has its own type — the type of the animal corresponding to this figure (the horse, the tiger and so on). The type of animal of the $ i $ -th figure equals $ t_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1328D/6fef0d63a3e427398bbe634881f56ca00339f29a.png)The example of the carousel for $ n=9 $ and $ t=[5, 5, 1, 15, 1, 5, 5, 1, 1] $ . You want to color each figure in one of the colors. You think that it's boring if the carousel contains two different figures (with the distinct types of animals) going one right after another and colored in the same color.

Your task is to color the figures in such a way that the number of distinct colors used is the minimum possible and there are no figures of the different types going one right after another and colored in the same color. If you use exactly $ k $ distinct colors, then the colors of figures should be denoted with integers from $ 1 $ to $ k $ .

## 样例 #1

### 输入

```
4
5
1 2 1 2 2
6
1 2 2 1 2 2
5
1 2 1 2 3
3
10 10 10```

### 输出

```
2
1 2 1 2 2
2
2 1 2 1 2 1
3
2 3 2 3 1
1
1 1 1```

# AI分析结果

【题目内容（中文重写）】
# 旋转木马

## 题目描述
圆形旋转木马由 $n$ 个动物造型组成。这些造型按旋转木马的转动顺序从 $1$ 到 $n$ 编号。因此，在第 $n$ 个造型之后是编号为 $1$ 的造型。每个造型都有其对应的动物类型（如马、老虎等）。第 $i$ 个造型的动物类型用 $t_i$ 表示。

![旋转木马示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1328D/6fef0d63a3e427398bbe634881f56ca00339f29a.png)
这里是一个 $n = 9$ 且 $t = [5, 5, 1, 15, 1, 5, 5, 1, 1]$ 的旋转木马示例。

你想给每个造型涂上一种颜色。你认为如果旋转木马上有两个不同的造型（动物类型不同）相邻且涂成相同的颜色，那就太单调了。

你的任务是给这些造型涂色，使得使用的不同颜色的数量尽可能少，并且相邻的不同类型的造型不会涂成相同的颜色。如果你恰好使用了 $k$ 种不同的颜色，那么造型的颜色应该用从 $1$ 到 $k$ 的整数表示。

## 样例 #1

### 输入
```
4
5
1 2 1 2 2
6
1 2 2 1 2 2
5
1 2 1 2 3
3
10 10 10
```

### 输出
```
2
1 2 1 2 2
2
2 1 2 1 2 1
3
2 3 2 3 1
1
1 1 1
```

【算法分类】
构造

【综合分析与结论】
这些题解的核心思路都是通过分类讨论来确定最少使用的颜色数量并给出涂色方案。主要的分类依据包括所有造型的动物类型是否相同、造型数量的奇偶性以及是否存在相邻且动物类型相同的造型。

各题解的思路和要点基本一致，都是先判断所有造型的动物类型是否相同，若相同则全部涂成一种颜色；若不同，则根据造型数量的奇偶性和相邻造型的情况进一步讨论。对于偶数个造型，通常交替涂两种颜色；对于奇数个造型，若有相邻且相同的造型，则可以通过特殊处理使颜色数为 2，若没有则需要使用 3 种颜色。

解决的难点在于对各种情况的全面考虑和准确判断，特别是在奇数个造型且存在相邻相同造型的情况，需要找到合适的处理方法来保证相邻不同类型的造型颜色不同。

【所选题解】
- **WYXkk（5星）**
    - **关键亮点**：思路清晰，代码结构良好，通过定义宏和模板函数提高了代码的复用性和可读性。对各种情况的分类讨论明确，注释详细。
- **do_while_true（4星）**
    - **关键亮点**：对每种情况的分析详细，代码简洁明了，使用 `set` 来判断不同动物类型的数量，逻辑清晰。
- **ZZ作者（4星）**
    - **关键亮点**：对题目进行了详细的分析和分类讨论，给出了具体的例子帮助理解，代码实现思路清晰，注释丰富。

【重点代码】
### WYXkk
```cpp
q=rd();
while(q--)
{
    n=rd();
    F(i,1,n) rd(t[i]);
    bool flg1=false,flg2=false;
    int x;
    t[n+1]=t[1];
    F(i,1,n) if(t[i]==t[i+1]) flg1=true,x=i;else flg2=true;
    if(!flg2)
    {
        puts("1");
        F(i,1,n) printf("1 ");puts("");
    }
    else
    {
        if(!(n&1))
        {
            puts("2");
            F(i,1,n) printf("%d ",(i&1)+1);puts("");
        }
        else if(flg1)
        {
            puts("2");
            F(i,1,n) c[(x+i-1)%n+1]=i&1;
            F(i,1,n) printf("%d ",c[i]+1);
            puts("");
        }
        else
        {
            puts("3");
            F(i,1,n-1) printf("%d ",(i&1)+1);
            puts("3");
        }
    }
}
```
**核心实现思想**：先读取输入，然后判断是否所有造型的动物类型相同。若相同则全部涂成 1；若不同，再根据造型数量的奇偶性和是否有相邻相同的造型进行分类讨论，分别输出相应的颜色方案。

### do_while_true
```cpp
scanf("%d",&T);
while(T--)
{
    set<int>s;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s.insert(a[i]);
    }
    if(s.size()==1)
    {
        puts("1");
        for(int i=1;i<=n;i++)
            printf("1 ");
        puts("");
        continue;
    }
    else if(s.size()==2)
    {
        int tmp=a[1];
        puts("2");
        for(int i=1;i<=n;i++)
        {
            if(tmp==a[i]) printf("1 ");
            else printf("2 ");
        }
        puts("");
        continue;
    }
    if(n%2==0)
    {
        puts("2");
        for(int i=1;i<=n;i++)
            printf("%d ",i%2+1);
        puts("");
        continue;
    }
    int tmp=0;
    a[0]=a[n];
    for(int i=1;i<=n;i++)
        if(a[i]==a[(i+1)%n]) tmp=i;
    if(!tmp)
    {
        puts("3");
        for(int i=1;i<n;i++)
            printf("%d ",2-i%2);
        puts("3");
        continue;
    }
    int cnt=1;
    puts("2");
    for(int i=1;i<=n;i++){
        printf("%d ",2-cnt%2);
        if(i!=tmp) cnt++;
    }
    puts("");
}
```
**核心实现思想**：使用 `set` 来判断不同动物类型的数量。若只有一种类型，则全部涂成 1；若有两种类型，则分别涂成 1 和 2。对于偶数个造型，交替涂 1 和 2；对于奇数个造型，若有相邻相同的造型，则特殊处理使颜色数为 2，若没有则使用 3 种颜色。

### ZZ作者
```c++
cin>>t;
while(t--)
{
    cin>>a;
    flag=1;flag3=0;
    memset(num,0,sizeof(num));
    cin>>num[1];
    for(int i=2;i<=a;i++)
    {
        cin>>num[i];
        if(num[i]!=num[i-1])flag=0;
    }
    if(flag)
    {
        cout<<1<<endl;
        for(int i=1;i<=a;i++)cout<<1<<' ';
        cout<<endl;
    }
    else if(a%2==0||num[1]==num[a])
    {
        cout<<2<<endl;
        for(int i=1;i<=a;i++)cout<<(i%2)+1<<' ';
        cout<<endl;
    }
    else if(num[1]!=num[a])
    {
        for(int i=2;i<=a;i++)
        {
            if(num[i]==num[i-1])flag3=1;
        }
        if(flag3)
        {
            ll flag4=0;
            cout<<2<<endl;
            for(int i=1;i<=a;i++)
            {
                if(num[i]==num[i-1]&&flag4==0)
                {
                    flag4=1;
                }
                cout<<(i-flag4)%2+1<<' ';
            }
            cout<<endl;
        }
        else
        {
            cout<<3<<endl;
            for(int i=1;i<=a;i++)
            {
                if(num[i]==num[1])cout<<3<<' ';
                else cout<<(i%2)+1<<' ';
            }
            cout<<endl;
        }
    }
}
```
**核心实现思想**：先判断所有造型的动物类型是否相同，若相同则全部涂成 1。对于不同的情况，根据造型数量的奇偶性和首尾是否相同以及是否有相邻相同的造型进行分类讨论，输出相应的颜色方案。

【最优关键思路或技巧】
- 分类讨论：通过对所有造型的动物类型是否相同、造型数量的奇偶性以及是否存在相邻且动物类型相同的造型进行分类讨论，逐步确定最少使用的颜色数量和涂色方案。
- 利用环的特性：在处理奇数个造型且存在相邻相同造型的情况时，通过特殊处理相邻相同的造型，将环转化为链的问题来解决。

【可拓展之处】
同类型题可能会改变条件，如增加颜色的限制、改变相邻造型的定义（如间隔几个造型也算相邻）等。类似的算法套路是通过分类讨论和构造的方法，根据不同的条件来确定最优方案。

【推荐题目】
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)

【个人心得】
- **ZZ作者**：这道题没有考察什么高级算法，但是考察了分类讨论的能力，作者第三次才A掉。作者认为一定要敢想，如果过不去，要自己多造数据，争取全面考虑每一种情况。这说明在解决这类需要分类讨论的问题时，要注重细节，全面考虑各种可能的情况，通过多造数据来验证自己的思路。

---
处理用时：66.61秒