// @ts-check
import { defineConfig } from 'astro/config';
import sitemap from '@astrojs/sitemap';

// https://astro.build/config
export default defineConfig({
    base: '/xournalpp-pluginhub/',
    integrations: [sitemap()],
  site: 'https://shadowdara.github.io'
});
