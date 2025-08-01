// @ts-check
import { defineConfig } from 'astro/config';
import sitemap from '@astrojs/sitemap';

export const base_url = '/xournalpp-pluginhub/'

// https://astro.build/config
export default defineConfig({
    base: base_url,
    integrations: [sitemap()],
  site: 'https://shadowdara.github.io'
});
