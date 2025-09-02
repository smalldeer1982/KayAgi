# [CERC2013] Digraphs

## 题目描述

有一些有向字母对，构造一个尽量大（最大 $20\times20$）的方阵，使得这个方阵中任意两个相邻字母对（从左到右或从上到下）都不是这些有向字母对中的一个。

## 样例 #1

### 输入

```
2
628
aa
az
ba
bb
bc
bd
be
bf
bg
bh
bi
bj
bk
bl
bm
bn
bo
bp
bq
br
bs
bt
bu
bv
bw
bx
by
ca
cb
cc
cd
ce
cf
cg
ch
ci
cj
ck
cl
cm
cn
co
cp
cq
cr
cs
ct
cu
cv
cw
cx
cy
da
db
dc
dd
de
df
dg
dh
di
dj
dk
dl
dm
dn
do
dp
dq
dr
ds
dt
du
dv
dw
dx
dy
ea
eb
ec
ed
ee
ef
eg
eh
ei
ej
ek
el
em
en
eo
ep
eq
er
es
et
eu
ev
ew
ex
ey
fa
fb
fc
fd
fe
ff
fg
fh
fi
fj
fk
fl
fm
fn
fo
fp
fq
fr
fs
ft
fu
fv
fw
fx
fy
ga
gb
gc
gd
ge
gf
gg
gh
gi
gj
gk
gl
gm
gn
go
gp
gq
gr
gs
gt
gu
gv
gw
gx
gy
ha
hb
hc
hd
he
hf
hg
hh
hi
hj
hk
hl
hm
hn
ho
hp
hq
hr
hs
ht
hu
hv
hw
hx
hy
ia
ib
ic
id
ie
if
ig
ih
ii
ij
ik
il
im
in
io
ip
iq
ir
is
it
iu
iv
iw
ix
iy
ja
jb
jc
jd
je
jf
jg
jh
ji
jj
jk
jl
jm
jn
jo
jp
jq
jr
js
jt
ju
jv
jw
jx
jy
ka
kb
kc
kd
ke
kf
kg
kh
ki
kj
kk
kl
km
kn
ko
kp
kq
kr
ks
kt
ku
kv
kw
kx
ky
la
lb
lc
ld
le
lf
lg
lh
li
lj
lk
ll
lm
ln
lo
lp
lq
lr
ls
lt
lu
lv
lw
lx
ly
ma
mb
mc
md
me
mf
mg
mh
mi
mj
mk
ml
mm
mn
mo
mp
mq
mr
ms
mt
mu
mv
mw
mx
my
na
nb
nc
nd
ne
nf
ng
nh
ni
nj
nk
nl
nm
nn
no
np
nq
nr
ns
nt
nu
nv
nw
nx
ny
oa
ob
oc
od
oe
of
og
oh
oi
oj
ok
ol
om
on
oo
op
oq
or
os
ot
ou
ov
ow
ox
oy
pa
pb
pc
pd
pe
pf
pg
ph
pi
pj
pk
pl
pm
pn
po
pp
pq
pr
ps
pt
pu
pv
pw
px
py
qa
qb
qc
qd
qe
qf
qg
qh
qi
qj
qk
ql
qm
qn
qo
qp
qq
qr
qs
qt
qu
qv
qw
qx
qy
ra
rb
rc
rd
re
rf
rg
rh
ri
rj
rk
rl
rm
rn
ro
rp
rq
rr
rs
rt
ru
rv
rw
rx
ry
sa
sb
sc
sd
se
sf
sg
sh
si
sj
sk
sl
sm
sn
so
sp
sq
sr
ss
st
su
sv
sw
sx
sy
ta
tb
tc
td
te
tf
tg
th
ti
tj
tk
tl
tm
tn
to
tp
tq
tr
ts
tt
tu
tv
tw
tx
ty
ua
ub
uc
ud
ue
uf
ug
uh
ui
uj
uk
ul
um
un
uo
up
uq
ur
us
ut
uu
uv
uw
ux
uy
va
vb
vc
vd
ve
vf
vg
vh
vi
vj
vk
vl
vm
vn
vo
vp
vq
vr
vs
vt
vu
vv
vw
vx
vy
wa
wb
wc
wd
we
wf
wg
wh
wi
wj
wk
wl
wm
wn
wo
wp
wq
wr
ws
wt
wu
wv
ww
wx
wy
xa
xb
xc
xd
xe
xf
xg
xh
xi
xj
xk
xl
xm
xn
xo
xp
xq
xr
xs
xt
xu
xv
xw
xx
xy
ya
yb
yc
yd
ye
yf
yg
yh
yi
yj
yk
yl
ym
yn
yo
yp
yq
yr
ys
yt
yu
yv
yw
yx
yy
za
zb
zc
zd
ze
zf
zg
zh
zi
zj
zk
zl
zm
zn
zo
zp
zq
zr
zs
zt
zu
zv
zw
zx
zy
zz
2
aa
bb
```

### 输出

```
aw
wz
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
```

# 题解

## 作者：封禁用户 (赞：3)

>本题是 CERC 2013 Problem K。
>
>本题在 CodeForces 上有提交通道：[Gym 100299K](https://codeforces.com/gym/100299)。

_感谢 [Gcc\_Gdb\_7\_8\_1](https://www.luogu.com.cn/user/1058410) 草拟这一算法的名称。_

~~FBWF（Floyd-Bellman-Warshall-Ford）模板题！~~

很明显，每个字符矩阵都存在一个最长的字符链。比如：

```plain
*.........
*.........
*.........
*.........
*.........
*.........
*.........
*.........
*.........
**********
```

因此，我们需要找到可能出现的最长字符链，然后构造字符矩阵：

```plain
0123456789
123456789A
23456789AB
3456789ABC
456789ABCD
56789ABCDE
6789ABCDEF
789ABCDEFG
89ABCDEFGH
9ABCDEFGHI
```

由于 $20 \times 20$ 的字符矩阵所需的的最长字符链的长度为 $20 \times 2-1=39$，而本题中字符链的长度最长为 $26-1=25$（`abc...z`），因此字符矩阵一定不会超出 $20 \times 20$ 的限制，除非……存在一个字符环。

这个问题便转化为：给定一张 $m=26$ 个结点的有向图，你需要找出有向图中的任意一个（或任意一条最长路径）。

这一问题可以用 Floyd-Warshall 和 Bellman-Ford 的结合体（~~Floyd-Bellman-Warshall-Ford，FBWF~~）解决：设 $u_{a,b,c}$ 表示：

- 是否存在长度为 $c$ 的从 $a$ 到 $b$ 的路径；
- 如果有，那么最后一条边是什么。

按 $c$ 升序转移即可。转移结束后，如果存在任意长度的从某个结点到自己的路径，那么存在环。如果没有，那么可以从 $m$ 开始枚举最长路径的长度。按照上面的办法找到路径的终点（或环上的某一个结点）后，就可以倒着找出整个路径（或环）了。

最终的时间复杂度为 $O(Tm^4)$，空间复杂度为 $O(m^3)$。数据中 $T \le 111$，因此这是可以通过的。

**AC Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;
bool s[32][32],o[32];
int u[32][32][32];
char r[52];
int go()
{
    int n;
    cin>>n;
    memset(s,0,sizeof s);
    memset(u,0,sizeof u);
    memset(r,0,sizeof r);
    memset(o,0,sizeof o);
    for(int i=1;i<=n;i++)
    {
        char x,y;
        cin>>x>>y;
        x-=96;
        y-=96;
        s[x][y]=true;
    }
    for(int i=1;i<=27;i++)
        s[i][27]=true;
    for(int i=1;i<=27;i++)
        s[27][i]=true;
    for(int i=1;i<=27;i++)
        u[i][i][0]=-1;
    for(int i=1;i<=27;i++)
        for(int j=1;j<=27;j++)
            for(int k=1;k<=27;k++)
                for(int l=1;l<=27;l++)
                {
                    if(s[j][k]) continue;
                    if(!u[l][j][i-1]) continue;
                    u[l][k][i]=j;
                }
    int c=0,d=0,e=0;
    for(d=1;d<=27;d++)
    {
        for(int i=1;i<=27;i++)
            if(u[i][i][d])
            {
                c=i;
                break;
            }
        if(c) break;
    }
    if(c==0)
    {
        d=27;
        for(d=27;d>=1;d--)
        {
            c=0,e=0;
            for(int i=1;i<=27;i++)
            {
                if(c) break;
                for(int j=1;j<=27;j++)
                if(u[i][j][d])
                {
                    c=i;
                    e=j;
                    break;
                }
            }
            if(c) break;
        }
        r[d+1]=e;
        for(int i=d;i>=1;i--)
        {
            e=u[c][e][i];
            r[i]=e;
        }
        if(d<=1) cout<<'a'<<endl;
        else
        {
            for(int i=1;i<=d/2+1;i++)
            {
                for(int j=1;j<=d/2+1;j++)
                    cout<<(char)(r[i+j-1]+96);
                cout<<endl;
            }
        }
    }
    else
    {
        r[d]=c;
        int p=d;
        for(p=d-1;p>=1;p--)
        {
            c=u[r[d]][c][p+1];
            r[p]=c;
        }
        for(int i=d+1;i<=39;i++)
            r[i]=r[i-d];
        for(int i=1;i<=20;i++)
        {
            for(int j=1;j<=20;j++)
                cout<<(char)(r[i+j-1]+96);
            cout<<endl;
        }
    }
    return 0;
}
int main()
{
    int T;
    cin>>T;
    while(T--) go();
}
```

---

