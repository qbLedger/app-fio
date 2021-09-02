#include "bip44.h"
#include "signTransaction.h"

#include "securityPolicy.h"




#define DENY()                          return POLICY_DENY;
#define DENY_IF(expr)      if (expr)    return POLICY_DENY;
#define DENY_UNLESS(expr)  if (!(expr)) return POLICY_DENY;

#define WARN_IF(expr)      if (expr)    return POLICY_PROMPT_WARN_UNUSUAL;
#define WARN_UNLESS(expr)  if (!(expr)) return POLICY_PROMPT_WARN_UNUSUAL;

#define PROMPT()                        return POLICY_PROMPT_BEFORE_RESPONSE;
#define PROMPT_IF(expr)    if (expr)    return POLICY_PROMPT_BEFORE_RESPONSE;

#define ALLOW()                         return POLICY_ALLOW_WITHOUT_PROMPT;
#define ALLOW_IF(expr)     if (expr)    return POLICY_ALLOW_WITHOUT_PROMPT;

#define SHOW()                          return POLICY_SHOW_BEFORE_RESPONSE;
#define SHOW_IF(expr)      if (expr)    return POLICY_SHOW_BEFORE_RESPONSE;
#define SHOW_UNLESS(expr)  if (!(expr)) return POLICY_SHOW_BEFORE_RESPONSE;


// Get extended public key and return it to the host
security_policy_t policyForGetPublicKey(const bip44_path_t* pathSpec)
{
	DENY_UNLESS(bip44_hasValidFIOPrefix(pathSpec));
	DENY_UNLESS(bip44_containsAddress(pathSpec));
    DENY_IF(bip44_containsMoreThanAddress(pathSpec));
	WARN_UNLESS(bip44_hasReasonableAddress(pathSpec));

	PROMPT();
}

security_policy_t policyForSignTxInit(network_type_t network)
{
	DENY_IF(network == NETWORK_UNKNOWN);
	SHOW();
}

security_policy_t policyForSignTxHeader()
{
	SHOW();
}

security_policy_t policyForSignTxActionHeader(action_type_t action)
{
	DENY_IF(action == ACTION_TYPE_UNKNOWN);
	SHOW();
}

security_policy_t policyForSignTxActionAuthorization()
{
	SHOW();
}

security_policy_t policyForSignTxActionData()
{
	SHOW();
}

security_policy_t policyForSignTxWitnesses(const bip44_path_t* pathSpec)
{
	DENY_UNLESS(bip44_hasValidFIOPrefix(pathSpec));
	DENY_UNLESS(bip44_containsAddress(pathSpec));
    DENY_IF(bip44_containsMoreThanAddress(pathSpec));

	PROMPT();
}





