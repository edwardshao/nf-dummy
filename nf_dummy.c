#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Shao <laface.tw@gmail.com>");
MODULE_DESCRIPTION("Dummy Netfilter module");

static unsigned int dummy_ipv4_in(const struct nf_hook_ops *ops,
				  struct sk_buff *skb,
				  const struct nf_hook_state *state)
{
	printk(KERN_DEBUG "dummy_ipv4_in in\n");	
	
	return NF_ACCEPT;
}

static struct nf_hook_ops nf_dummy_ipv4_ops[] __read_mostly = {
	{
		.hook		= dummy_ipv4_in,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP_PRI_RAW,
	},
};

static int __init nf_dummy_init(void)
{
	int err;

	printk(KERN_DEBUG "nf_dummy_init\n");	

	err = nf_register_hooks(nf_dummy_ipv4_ops, ARRAY_SIZE(nf_dummy_ipv4_ops));

	return err;
}

static void __exit nf_dummy_exit(void)
{
	nf_unregister_hooks(nf_dummy_ipv4_ops, ARRAY_SIZE(nf_dummy_ipv4_ops));

	printk(KERN_DEBUG "nf_dummy_exit\n");	
}

module_init(nf_dummy_init);
module_exit(nf_dummy_exit);
