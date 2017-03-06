/* UVALive :: Regionals 2010 :: North America - Rocky Mountain. Problem 4882 - Parenthesis, by Abreto <m@abreto.net>. */
#include <stdio.h>

#define MAXN    1024
#define NODE(i) (memory[(i)])
typedef struct _node
{
    char op;
    int l, r;
}node;
typedef int p_node;
const p_node NULL_NODE = 0;
node memory[MAXN];
p_node nodememoryindex[MAXN] = {0};

void init_memory(void)
{
    int i = 0;
    for(i = 0;i < MAXN;++i)
        nodememoryindex[i] = i+1;
    nodememoryindex[i-1] = 0;
}
p_node new_node(void)
{
    p_node x = nodememoryindex[0];
    nodememoryindex[0] = nodememoryindex[x];
    return x;
}

char line[MAXN] = {0};
char operator_stack[MAXN] = {0};
size_t operator_stack_top = 0;
p_node node_stack[MAXN] = {0};
size_t node_stack_top = 0;


void clear_stacks(void)
{
    operator_stack_top = node_stack_top = 0;
}
void push_op(char op)
{
    operator_stack[operator_stack_top++] = op;
}
char top_op(void)
{
    return operator_stack[operator_stack_top-1];
}
void pop_op(void)
{
    --operator_stack_top;
}
void push_node(p_node x)
{
    node_stack[node_stack_top++] = x;
}
p_node pop_node(void)
{
    return node_stack[--node_stack_top];
}
void push_var(char v)
{
    p_node i = new_node();
    NODE(i).op = v;
    NODE(i).l = NODE(i).r = NULL_NODE;
    node_stack[node_stack_top++] = i;
}

void do_calculation_once(void)
{
    p_node n = new_node();
    char ope = top_op();
    pop_op();
    NODE(n).op = ope;
    NODE(n).r = pop_node();
    NODE(n).l = pop_node();
    push_node(n);
}

void print_node(p_node x)
{
    if( x != NULL_NODE )
    {
        p_node left = NODE(x).l;
        p_node right = NODE(x).r;
        
        if( '*' == NODE(x).op )
        {
            if( (left != NULL_NODE) && ('+' == NODE(left).op) )
            {
                printf("("); print_node(left); printf(")");
            }
            else    print_node(left);
            if( (right != NULL_NODE) && ('+' == NODE(right).op) )
            {
                printf("("); print_node(right); printf(")");
            }
            else    print_node(right);
        }
        else
        {
            print_node(left);
            printf("%c", NODE(x).op);
            print_node(right);
        }
    }
}

#define IS_MULTI    ( (*(p-1) >= 'a' && *(p-1) <= 'z') || (')' == *(p-1)) )
void proccess(void)
{
    char *p = line;
    if( '(' == *p )
        push_op('(');
    else
        push_var(*p);
    while( *(++p) != '\0' )
    {
        if( '+' == *p )
        {
            while( '*' == top_op() )
                do_calculation_once();
            push_op('+');
        }
        else if ( '(' == *p )
        {
            if( IS_MULTI )
                push_op('*');
            push_op('(');
        }
        else if( ')' == *p )
        {
            while( '(' != top_op() )
                do_calculation_once();
            pop_op();
        }
        else    /* variables */
        {
            if( IS_MULTI )
                push_op('*');
            push_var(*p);
        }
    }
    while( operator_stack_top > 0 )
        do_calculation_once();
    print_node(node_stack[0]);
    printf("\n");
}

int main(void)
{
    while( gets(line) ) /* In fact, `gets` is not recommended. */
    {
        init_memory();
        clear_stacks();
        proccess();
    }
    return 0;
}
