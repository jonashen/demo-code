# -*- encoding : utf-8 -*-

set :rails_env, 'development'
set :whenever_environment, 'development'
set :domain, 'gbookst.iscreen.tw'

role :web, domain
role :app, domain
role :db, domain, :primary => true

set :deploy_to, "/opt/www/#{application}"
set :whenever_environment, rails_env
set :branch, 'develop'

# Event hooks
if restart_daemons
   before "deploy:update_code", "daemons:stop"
   after "deploy:restart", "daemons:start"
end

#before "bundle:install", "db:symblink"#, "deploy:gemspec_remove"

after "deploy:create_symlink", "deploy:cleanup"