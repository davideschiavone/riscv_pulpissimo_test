PULP_APP = test
PULP_APP_SRCS = testCSR.c

PULP_CFLAGS += -O3

ifeq '$(cluster)' '1'
PULP_CFLAGS += -DUSE_CLUSTER
endif

include $(PULP_SDK_HOME)/install/rules/pulp.mk
