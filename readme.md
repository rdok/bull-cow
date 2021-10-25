# Pioneer 0
[![test-site][test_site_badge]][test_site]
[![prod-site][prod_site_badge]][prod_site]

Word guessing game with Pioneer program theme; the first attempted launch beyond Earth.

### Deployment
> On Windows OS use [chocolatey][chocolatey] to install [Makefile][makefile_chocolatey].  
> Additional dependencies [awscli][awscli] and [awssamcli][awssamcli].  
 
See `Makefile`

### CI/CD
No CI/CD pipelines have been set up as there is currently no practical, open source solution for running Unreal Engine 4 through GitHub actions.

Instead, deploy the infrastructure & website manually locally through the ready made commands on Makefile.

[test_site_badge]: https://img.shields.io/badge/test-green?style=flat-square&logo=amazon-aws
[test_site]: https://pioneer0-test.rdok.co.uk/
[prod_site_badge]: https://img.shields.io/badge/prod-orange?style=flat-square&logo=amazon-aws
[prod_site]: https://pioneer0.rdok.co.uk/
[udemy]: https://www.udemy.com/course/unrealcourse/
[makefile_chocolatey]: https://community.chocolatey.org/packages/make
[chocolatey]: https://chocolatey.org/install
[awscli]: https://community.chocolatey.org/packages/awscli
[awssamcli]: https://community.chocolatey.org/packages/awssamcli
