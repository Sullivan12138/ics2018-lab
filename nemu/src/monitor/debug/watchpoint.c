#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_WP() {
    if(free_ == NULL) assert(0);
    WP* p = free_->next;
    WP* q = free_;
    free_->next = head;
    free_ = p;
    head = q;
    return head;
}

void free_wp(WP *wp) {
    if(wp == NULL) assert(0);
    WP *p;
    WP *q;
    p = head;
    q = NULL;
    while(p != NULL) {
        if(p -> NO == head->NO) {
            head = head->next;
            break;
        }
        if(p->NO == wp->NO) {
            q->next = p->next;
            break;
        }
        else {
            q = p;
            p = p->next;
        }
    }
    if(p == NULL) assert(0);
    WP *r;
    r = free_;
    free_ = wp;
    wp->next = r;
}
