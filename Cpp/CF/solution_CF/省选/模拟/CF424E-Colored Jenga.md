# Colored Jenga

## 题目描述

Cold winter evenings in Tomsk are very boring — nobody wants be on the streets at such a time. Residents of Tomsk while away the time sitting in warm apartments, inventing a lot of different games. One of such games is 'Colored Jenga'.

This game requires wooden blocks of three colors: red, green and blue. A tower of $ n $ levels is made from them. Each level consists of three wooden blocks. The blocks in each level can be of arbitrary colors, but they are always located close and parallel to each other. An example of such a tower is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424E/5bfa10b7ff0cc446ecac2856516e57c041e0fdb2.png)The game is played by exactly one person. Every minute a player throws a special dice which has six sides. Two sides of the dice are green, two are blue, one is red and one is black. The dice shows each side equiprobably.

If the dice shows red, green or blue, the player must take any block of this color out of the tower at this minute so that the tower doesn't fall. If this is not possible, the player waits until the end of the minute, without touching the tower. He also has to wait until the end of the minute without touching the tower if the dice shows the black side. It is not allowed to take blocks from the top level of the tower (whether it is completed or not).

Once a player got a block out, he must put it on the top of the tower so as to form a new level or finish the upper level consisting of previously placed blocks. The newly constructed levels should have all the same properties as the initial levels. If the upper level is not completed, starting the new level is prohibited.

For the tower not to fall, in each of the levels except for the top, there should be at least one block. Moreover, if at some of these levels there is exactly one block left and this block is not the middle block, the tower falls.

The game ends at the moment when there is no block in the tower that you can take out so that the tower doesn't fall.

Here is a wonderful game invented by the residents of the city of Tomsk. I wonder for how many minutes can the game last if the player acts optimally well? If a player acts optimally well, then at any moment he tries to choose the block he takes out so as to minimize the expected number of the game duration.

Your task is to write a program that determines the expected number of the desired amount of minutes.

## 样例 #1

### 输入

```
6
RGB
GRG
BBB
GGR
BRG
BRB
```

### 输出

```
17.119213696601992
```

# 题解

## 作者：Milmon (赞：6)

[Milmon Page 链接：https://molmin.github.io/problem?id=21#solution](https://molmin.github.io/problem?id=21#solution)

仔细观察可以发现以下几点：

**结论 1：有效层总数不会超过 $n+1$。** 若一层中只有中间的位置有木板或者两边的位置有木板，则此层事实上已经没有实际用处，不妨删除该层。塔的下部每层至多抽出 $2$ 块后该层无效，而在上部添加一层需要 $3$ 块木板。

**结论 2：任意两层非顶层的有效层，可以任意交换。**（这是显然的）

**结论 3：任意一层有效层的左右两个位置对称，可以交换。**（这也是显然的）

考虑状态压缩。

对于一个塔的状态，每一层一个位置有四种状态：放置了木板（三种颜色），以及没有放置木板。而每一层有三个位置，需要占用 $6$ 个二进制位。对于一个塔的状态，有效层至多 $n+1\leq 7$ 层，即至多占用 $6\times 7=42$ 个二进制位，只需使用 `unsigned long long` 存储即可。

每一次状态转移枚举投掷出的三种颜色（投掷出黑色的情况可以 $\Theta(1)$ 处理），再枚举删除的是哪一块该色木板，最后枚举放置在顶层的哪个位置即可。

具体细节见代码实现。

[Code 链接：https://molmin.github.io/problem?id=21#code](https://molmin.github.io/problem?id=21#code)

---

## 作者：f_x_f (赞：0)

这题本身模型不难，直接进行记忆化搜索算出每个状态的答案即可。 这题的
关键在于状态数量的优化，有几个比较关键的优化点（其余一些细节 可以参考
标程）：

1、顶层以下所有的层都是无序的。

2、每层只需要记录能抽出的木板的状态即可，如果一层不能抽出木板了，那
么就可以在状态表示中删掉这一层。

3、每层中的两侧是对称的。 实现时，将状态进行 hash 判重，或者使用 STL
实现应该也可以（没试过） 做完以上优化后，对于一个 6 层的叠叠乐游戏，在
标程中不同的状态数量不 超过 20W，足以在出题人的机子上 1s 内求得结果。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace jenga {
    inline char get_unempty_char()
    {
        char ch;
        while(isspace(ch=getchar())) ;
        return ch;
    }
    const double eps(1e-12),Inf=1e+64;
    typedef unsigned long long i64u;
    const int RED=1,BLUE=2,GREEN=3,EMPTY=0,N=6,Base=67,mod=1<<20,modd=mod-1;
    int n,last[mod]={},next[mod]={},total_edge=0,s[N*3-1]={},tot=0;
    int order[1<<6]={};
    i64u hv[mod]={};
    double f[mod]={};
        inline void add(i64u hash,double v){
            int u=hash&modd;
            next[++total_edge]=last[u];
            last[u]=total_edge;
            f[total_edge]=v;
            hv[total_edge]=hash;
        }
        inline int get_num(char ch){
            if(ch=='R') 
                return RED;
            if(ch=='B') 
                return BLUE;
            if(ch=='G') 
                return GREEN;
            if(ch=='E') 
                return EMPTY;
            assert(false);
        }
        void init(){
            n=get_unempty_char()-'0';
            for(int a=0;a<=3;++a)
                for(int b=0;b<=3;++b)
                    for(int c=0;c<=3;++c)
                        order[a|(b<<2)|(c<<4)]=a<c?(a|(b<<2)|(c<<4)):(c|(b<<2)|(a<<4));
            for(int i=1;i<=n;++i){
                s[i]|=get_num(get_unempty_char())<<0;
                s[i]|=get_num(get_unempty_char())<<2;
                s[i]|=get_num(get_unempty_char())<<4;
                s[i]=order[s[i]];
            }
            tot=n;
        }
        inline i64u hash(int *s,int k,int up){
            static int v[N*3+10]={};
            i64u h=0;
            int tot=0;
            for(int i=1;i<=k;++i)
                if(s[i])
                    v[++tot]=s[i];
            sort(v+1,v+tot+1);
            for(int i=1;i<=tot;++i)
                h=h*Base+v[i];
            h=h*Base+up;
            return h;
        }
        double work(int *s,int tot,int up){
        up=order[up];
        i64u h=hash(s,tot,up);
        for(int i=last[h&modd];i;i=next[i])
            if(hv[i]==h)
                return f[i];
        double v[4]={Inf,Inf,Inf,Inf};
        int to=tot,D=6;
        if((up&3) && ((up>>2)&3) && ((up>>4)&3))
            s[++to]=up , up=0;
        for(int i=1;i<=tot;++i){
            int c1=s[i]&3,c2=(s[i]>>2)&3,c3=(s[i]>>4)&3,ns=s[i];
            if(c1 && c2 && c3 && v[c2]>eps){
                s[i]=0;
                if(!(up&3))
                    v[c2]=min(v[c2],work(s,to,up|c2));
                else if(!(up>>4&3))
                    v[c2]=min(v[c2],work(s,to,up|c2<<4));
                if(!(up>>2&3))
                    v[c2]=min(v[c2],work(s,to,up|c2<<2));
                s[i]=ns;
            }
            if(c1 && v[c1]>eps){
                s[i]=c3;
                if(!(up&3))
                    v[c1]=min(v[c1],work(s,to,up|c1));
                else if(!(up>>4&3))
                    v[c1]=min(v[c1],work(s,to,up|c1<<4));
                if(!(up>>2&3))
                    v[c1]=min(v[c1],work(s,to,up|c1<<2));
                s[i]=ns;
            }
            if(c3 && v[c3]>eps){
                s[i]=c1;
                if(!(up&3))
                    v[c3]=min(v[c3],work(s,to,up|c3));
                else if(!(up>>4&3))
                    v[c3]=min(v[c3],work(s,to,up|c3<<4));
                if(!(up>>2&3))
                    v[c3]=min(v[c3],work(s,to,up|c3<<2));
                s[i]=ns;
            }
        }
        double sum=0;
        if(v[1]!=Inf) sum+=v[1] , D-=1;
        if(v[2]!=Inf) sum+=v[2]*2 , D-=2;
        if(v[3]!=Inf) sum+=v[3]*2 , D-=2;
        sum=D==6 ? 0 : (sum+6)/(6-D);
        add(h,sum);
        return sum;
    }
    int Main(){
        init();
        printf("%.7f\n",work(s,tot-1,s[tot]));
        return 0;
    }
}
int main(){
    jenga::Main();
    return 0;
}
```

---

