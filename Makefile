deploy:
	sam build
	sam deploy \
		--guided \
	  --s3-bucket "rdok-test-deployments" \
	  --s3-prefix "pioneer0" \
	  --capabilities CAPABILITY_IAM
#       --no-fail-on-empty-changeset \
#       --parameter-overrides \
#         Name="${NAME}" \
#         Environment="${{ steps.env.outputs.environment }}" \
#         DBSecurityGroupId="${{ steps.env.outputs.db-security-group-id }}" \
#         PrivateVpcId="${{ steps.env.outputs.vpc-id }}" \
#         PrivateSubnetId1="${{ steps.env.outputs.subnet1 }}" \
#         PrivateSubnetId2="${{ steps.env.outputs.subnet2 }}" \
#         Timestamp="${TIMESTAMP}"
