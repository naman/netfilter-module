#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/tcp.h>


static struct nf_hook_ops hook_options;

/**
 * [hook functiion ]
 * @param  hooknum [description]
 * @param  skb     [description]
 * @param  in      [description]
 * @param  out     [description]
 * @param  okfn    [description]
 * @return         [action]
 */
unsigned int hook_function(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *)){

        struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
        struct tcphdr *tcp_header;

        if (ip_header->protocol == IPPROTO_TCP) {
                // printk(KERN_INFO "TCP packet detected!\n");

                tcp_header = (struct tcphdr *) skb_transport_header(skb);

                /**
                 * NULL Scan
                 */
                if (tcp_header->syn == 0
                    && tcp_header->ack == 0
                    && tcp_header->urg == 0
                    && tcp_header->rst == 0
                    && tcp_header->fin == 0
                    && tcp_header->psh == 0) {
                        printk(KERN_INFO "NULL Scan detected!\n");
                }


                /**
                 * ACK Scan
                 */
                else if (tcp_header->syn == 0
                         && tcp_header->ack == 1
                         && tcp_header->urg == 0
                         && tcp_header->rst == 0
                         && tcp_header->fin == 0
                         && tcp_header->psh == 0) {

                        printk(KERN_INFO "ACK Scan detected!\n");
                }



                /**
                 * FIN Scan
                 */
                else if (tcp_header->syn == 0
                         && tcp_header->ack == 0
                         && tcp_header->urg == 0
                         && tcp_header->rst == 0
                         && tcp_header->fin == 1
                         && tcp_header->psh == 0) {

                        printk(KERN_INFO "FIN Scan detected!\n");
                }


                /**
                 * XMAS Scan
                 */
                else if (tcp_header->syn == 0
                         && tcp_header->ack == 0
                         && tcp_header->urg == 1
                         && tcp_header->rst == 0
                         && tcp_header->fin == 1
                         && tcp_header->psh == 1) {

                        printk(KERN_INFO "XMAS Scan detected!\n");
                }

        }
        return NF_ACCEPT;
}

/**
 * [initialize module when insmod]
 * @return [0]
 */
static int __init initialize(void){
        hook_options.hook = hook_function;
        hook_options.hooknum = NF_INET_PRE_ROUTING;
        hook_options.pf = PF_INET;
        hook_options.priority = NF_IP_PRI_FIRST;

        nf_register_hook(&hook_options);
        return 0;
}

/**
 * [cleanup module]
 */
static void __exit cleanup(void){
        nf_unregister_hook(&hook_options);
}

module_init(initialize);
module_exit(cleanup);
